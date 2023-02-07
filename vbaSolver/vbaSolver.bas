Attribute VB_Name = "Module1"
Public Const NUM_DIGITS = 9
Public Const SQRT_DIG = 3

Sub solve()
Attribute solve.VB_ProcData.VB_Invoke_Func = " \n14"
    Dim mySheet As Worksheet
    
    Dim fixed(0 To NUM_DIGITS, 0 To NUM_DIGITS) As Boolean
    Dim individual(0 To NUM_DIGITS, 0 To NUM_DIGITS) As Integer
    
    Dim rowDigits(0 To NUM_DIGITS, 1 To NUM_DIGITS) As Boolean
    Dim colDigits(0 To NUM_DIGITS, 1 To NUM_DIGITS) As Boolean
    Dim boxDigits(0 To NUM_DIGITS, 1 To NUM_DIGITS) As Boolean
    
    Dim index As Integer
    Dim direction As Integer
    Dim row As Integer
    Dim col As Integer
    Dim toCheck As Integer
    Dim foundValidDigit As Boolean
    
    Set mySheet = ActiveSheet
    
    For I = 0 To NUM_DIGITS - 1
        For J = 0 To NUM_DIGITS - 1
            individual(I, J) = mySheet.Cells(I + 1, J + 1).Value
            fixed(I, J) = (individual(I, J) <> 0)
            If fixed(I, J) Then
                Dim K As Integer
                K = Int(I / SQRT_DIG) + SQRT_DIG * Int(J / SQRT_DIG)
                rowDigits(I, individual(I, J)) = True
                colDigits(J, individual(I, J)) = True
                boxDigits(K, individual(I, J)) = True
            End If
        Next J
    Next I
    
    index = 0
    direction = 1
    
    While index >= 0 And index < NUM_DIGITS * NUM_DIGITS
        row = Int(index / NUM_DIGITS)
        col = index Mod NUM_DIGITS
        If fixed(row, col) Then
            index = index + direction
        Else
            toCheck = individual(row, col)
            foundValidDigit = False
            box = Int(row / SQRT_DIG) + SQRT_DIG * Int(col / SQRT_DIG)
            If toCheck > 0 Then
                individual(row, col) = 0
                rowDigits(row, toCheck) = False
                colDigits(col, toCheck) = False
                boxDigits(box, toCheck) = False
            End If

            While toCheck < NUM_DIGITS And Not foundValidDigit
                toCheck = toCheck + 1
                foundValidDigit = Not (rowDigits(row, toCheck) Or colDigits(col, toCheck) Or boxDigits(box, toCheck))
            Wend
            
            If foundValidDigit Then
                individual(row, col) = toCheck
                rowDigits(row, toCheck) = True
                colDigits(col, toCheck) = True
                boxDigits(box, toCheck) = True
                direction = 1
            Else
                direction = -1
            End If
            
            index = index + direction
            
        End If
    Wend
    If index = -1 Then
        MsgBox ("unable to solve")
    End If
        
    
    For I = 0 To NUM_DIGITS - 1
        For J = 0 To NUM_DIGITS - 1
            mySheet.Cells(I + 1, J + 1).Value = individual(I, J)
        Next J
    Next I

End Sub

