Public Class Form1
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
    Friend WithEvents TextBox3 As System.Windows.Forms.TextBox
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents ListBox1 As System.Windows.Forms.ListBox
    Friend WithEvents Button2 As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.TextBox2 = New System.Windows.Forms.TextBox()
        Me.TextBox3 = New System.Windows.Forms.TextBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.ListBox1 = New System.Windows.Forms.ListBox()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(40, 48)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.Size = New System.Drawing.Size(216, 20)
        Me.TextBox1.TabIndex = 0
        Me.TextBox1.Text = "Ooos.exe"
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(48, 96)
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.Size = New System.Drawing.Size(88, 20)
        Me.TextBox2.TabIndex = 1
        Me.TextBox2.Text = "TextBox2"
        '
        'TextBox3
        '
        Me.TextBox3.Location = New System.Drawing.Point(144, 96)
        Me.TextBox3.Name = "TextBox3"
        Me.TextBox3.Size = New System.Drawing.Size(80, 20)
        Me.TextBox3.TabIndex = 2
        Me.TextBox3.Text = "TextBox3"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(232, 96)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(48, 24)
        Me.Button1.TabIndex = 3
        Me.Button1.Text = "Button1"
        '
        'ListBox1
        '
        Me.ListBox1.Location = New System.Drawing.Point(40, 144)
        Me.ListBox1.Name = "ListBox1"
        Me.ListBox1.Size = New System.Drawing.Size(224, 108)
        Me.ListBox1.TabIndex = 4
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(200, 16)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(48, 24)
        Me.Button2.TabIndex = 5
        Me.Button2.Text = "Button2"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(292, 273)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Button2, Me.ListBox1, Me.Button1, Me.TextBox3, Me.TextBox2, Me.TextBox1})
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub TextBox2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox2.TextChanged

    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Me.ListBox1.Items.Add(Me.TextBox2.Text & " : " & Me.TextBox3.Text)
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Microsoft.VisualBasic.FileOpen(1, Me.TextBox1.Text, OpenMode.Binary, OpenAccess.Read)
        FileOpen(2, Me.TextBox1.Text & ".bin", OpenMode.Binary, OpenAccess.ReadWrite)

        FileOpen(3, "ooosboot.bin", OpenMode.Binary, OpenAccess.Read)

        Dim temp As Byte

        Do
            Microsoft.VisualBasic.FileGet(3, temp)
            Microsoft.VisualBasic.FilePut(2, temp)
        Loop Until Microsoft.VisualBasic.EOF(3)
        FileClose(3)


        Dim Iter, i, TempString, StartBlock, EndBlock, BlockType1, BlockType2
        Iter = 0

        TempString = Me.ListBox1.Items.Item(0)
        EndBlock = CInt(Microsoft.VisualBasic.Left(TempString, InStr(TempString, " : ")))
        BlockType2 = CInt(Microsoft.VisualBasic.Right(TempString, Len(TempString) - InStr(TempString, " : ") - 2))

        BlockType1 = 0
        StartBlock = 0
        i = 0
        Do
            i = i + 1
            If i > EndBlock Then
                Iter = Iter + 1
                TempString = Me.ListBox1.Items.Item(Iter)
                StartBlock = EndBlock
                BlockType1 = BlockType2
                EndBlock = CInt(Microsoft.VisualBasic.Left(TempString, InStr(TempString, " : ")))
                BlockType2 = CInt(Microsoft.VisualBasic.Right(TempString, Len(TempString) - InStr(TempString, " : ") - 2))
            End If
            If BlockType1 = 0 Then
                Microsoft.VisualBasic.FileGet(1, temp)
            ElseIf BlockType1 = 1 Then
                Microsoft.VisualBasic.FileGet(1, temp)
                Microsoft.VisualBasic.FilePut(2, temp)
            Else
                temp = 0
                Microsoft.VisualBasic.FilePut(2, temp)
            End If
        Loop Until Microsoft.VisualBasic.EOF(1)

        FileClose(1)
        FileClose(2)

    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.ListBox1.Items.Add("0 : 0")
        Me.ListBox1.Items.Add("1024 : 2")
        Me.ListBox1.Items.Add("5120 : 1")
        Me.ListBox1.Items.Add("7168 : 2")
        Me.ListBox1.Items.Add("9216 : 1")
        Me.ListBox1.Items.Add("9728 : 2")
        Me.ListBox1.Items.Add("13312 : 1")
        Me.ListBox1.Items.Add("14336 : 0")



    End Sub
End Class
