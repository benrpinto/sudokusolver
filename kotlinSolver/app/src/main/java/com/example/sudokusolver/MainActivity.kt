package com.example.sudokusolver

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.InputType
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TableLayout
import android.widget.TableRow
import java.util.*

private const val NUM_DIGITS:Int = 9
private const val SQRT_DIG:Int = 3
private const val DEBUG: Boolean = false

class SudokuPuzzle (input : Vector<Vector<Int>>){
    private val individual: Vector<Vector<Int>> = Vector(NUM_DIGITS)
    private val fixedCell: Vector<Vector<Boolean>> = Vector(NUM_DIGITS)

    private val rowDigits: Vector<Vector<Boolean>> = Vector(NUM_DIGITS)
    private val colDigits: Vector<Vector<Boolean>> = Vector(NUM_DIGITS)
    private val boxDigits: Vector<Vector<Boolean>> = Vector(NUM_DIGITS)

    init{
        for(a in 0 until NUM_DIGITS){
            individual.add(Vector(NUM_DIGITS))
            fixedCell.add(Vector(NUM_DIGITS))

            rowDigits.add(Vector(NUM_DIGITS))
            colDigits.add(Vector(NUM_DIGITS))
            boxDigits.add(Vector(NUM_DIGITS))
            for (b in 0 until NUM_DIGITS){
                individual[a].add(0)
                fixedCell[a].add(false)

                rowDigits[a].add(false)
                colDigits[a].add(false)
                boxDigits[a].add(false)
            }
        }
        for(row in 0 until NUM_DIGITS){
            for(col in 0 until NUM_DIGITS){
                individual[row][col] = input[row][col]
                if(individual[row][col] > 0){
                    fixedCell[row][col] = true
                    val box:Int = (row/ SQRT_DIG) + (col/SQRT_DIG)* SQRT_DIG
                    rowDigits[row][individual[row][col]-1] = true
                    colDigits[col][individual[row][col]-1] = true
                    boxDigits[box][individual[row][col]-1] = true
                }
            }
        }
    }

    fun solve(): Boolean {
        var index = 0
        var direction = 1
        while (index >=0 && index < NUM_DIGITS* NUM_DIGITS){
            val row = index/ NUM_DIGITS
            val col = index.mod(NUM_DIGITS)
            if (!fixedCell[row][col]){
                var toCheck:Int = individual[row][col]
                var foundValidDigit = false
                val box:Int = (row/ SQRT_DIG) + (col/SQRT_DIG)* SQRT_DIG
                if(toCheck > 0){
                    individual[row][col] = 0
                    rowDigits[row][toCheck-1] = false
                    colDigits[col][toCheck-1] = false
                    boxDigits[box][toCheck-1] = false
                }
                while(toCheck < NUM_DIGITS && !foundValidDigit){
                    toCheck++
                    foundValidDigit = !(rowDigits[row][toCheck-1]||colDigits[col][toCheck-1]||boxDigits[box][toCheck-1])
                }
                if(foundValidDigit){
                    individual[row][col] = toCheck
                    rowDigits[row][toCheck-1]=true
                    colDigits[col][toCheck-1]=true
                    boxDigits[box][toCheck-1]=true
                    direction = 1
                }else{
                    direction = -1
                }
            }
            index += direction
        }
        return index >=0
    }

    fun display(): String{
        var toReturn = ""
        for(row in 0 until NUM_DIGITS) {
            for (col in 0 until NUM_DIGITS) {
                toReturn += individual[row][col].toString()
            }
            toReturn +="\n"
        }
        return toReturn
    }

    fun output(): Vector<Vector<Int>> {
        return individual
    }
}

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val visDigit:Vector<Vector<EditText>> = Vector(NUM_DIGITS)
        val visRow:Vector<TableRow> = Vector(NUM_DIGITS)
        val visSudoku:TableLayout = findViewById(R.id.sudokuDisplay)
        val visSolve:Button = findViewById(R.id.solve)

        for (a in 0 until NUM_DIGITS){
            visRow.add(TableRow(this))
            visSudoku.addView(visRow[a])
            visRow[a].layoutParams = TableRow.LayoutParams(
                TableRow.LayoutParams.MATCH_PARENT,
                TableRow.LayoutParams.MATCH_PARENT
            )
            visDigit.add(Vector(NUM_DIGITS))
            for (b in 0 until NUM_DIGITS){
                visDigit[a].add(EditText(this))
                visRow[a].addView(visDigit[a][b])
                visDigit[a][b].layoutParams = TableRow.LayoutParams(
                    TableRow.LayoutParams.MATCH_PARENT,
                    TableRow.LayoutParams.WRAP_CONTENT
                )
                visDigit[a][b].setEms(1)
                visDigit[a][b].inputType = InputType.TYPE_CLASS_NUMBER
                visDigit[a][b].textSize = 30.toFloat()
                visDigit[a][b].textAlignment = View.TEXT_ALIGNMENT_CENTER
                visDigit[a][b].setText("")
            }
        }

        visSolve.setOnClickListener{
            val digits:Vector<Vector<Int>> = Vector(NUM_DIGITS)
            for (a in 0 until NUM_DIGITS) {
                digits.add(Vector(NUM_DIGITS))
                for (b in 0 until NUM_DIGITS) {
                    val input =
                        try {
                            visDigit[a][b].text.toString().toInt()
                        }catch(e:NumberFormatException){
                            0
                        }
                    digits[a].add(input)
                    if(input<0 || input> NUM_DIGITS){
                        digits[a][b] = 0
                    }
                }
            }
            val mySud = SudokuPuzzle(digits)
            val solvable = mySud.solve()
            if(DEBUG){
                print(mySud.display())
            }
            if(solvable){
                val answer:Vector<Vector<Int>> = mySud.output()
                for (a in 0 until NUM_DIGITS) {
                    for (b in 0 until NUM_DIGITS) {
                        visDigit[a][b].setText(answer[a][b].toString())
                    }
                }
            }

        }


    }
}