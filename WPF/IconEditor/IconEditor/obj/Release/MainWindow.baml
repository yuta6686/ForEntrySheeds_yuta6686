   M S B A M L   `   `   `  ���� E  AIconEditor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:IconEditor
IconEditor      IconEditor.MainWindow   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     *localclr-namespace:IconEditor     D @ModernWpf, Version=0.9.4.0, Culture=neutral, PublicKeyToken=nullM IModernWpf.Controls, Version=0.9.4.0, Culture=neutral, PublicKeyToken=null,ui!http://schemas.modernwpf.com/2019     � Title$B  <☆スター・バースト・アイコン・エディタ☆�� � Icon$ Images/icon.png��0  *ModernWpf.Controls.Primitives.WindowHelper   UseModernWindowStyle .  J� CommandBindings )  #System.Windows.Input.CommandBinding  -      IconEditor.MainWindow   UndoCommand   Command# Z   -      RedoCommand# Z   -      SaveAsCommand# Z   -      CopyCommand# Z   -   	   PasteCommand# Z	 
 J� InputBindings
 ��  �� Gesture$ Ctrl+Z�� �� Command# Z �� $ Ctrl+Y��# Z �� $ Shift+Ctrl+Z��# Z �� $ Shift+Ctrl+S��# Z �� $ Ctrl+C��# Z �� $ Ctrl+V��# Z	  � 	Resources    BlueFill �� Color��%   &	        �� $
 Blue��.��� 
���   � � RowDefinitions �� $
��Auto ��� $
��Auto �$
��37.6���� �� $
��Auto �.+�o� $��0��$
��Auto��$��
0,0,-0.4,0q�.@�m� $�� ファイル(_F)��.@�m� -    m�Name$ MenuItem_New��$��
新規(_N)�� m� InputGestureText$ 	[Ctrl] N �� m� Icon �� $��Images/NewFile_16x.png��.@�m� -   $ MenuItem_NewIn_Empty��$��Empty��m� -   $ MenuItem_NewIn��$��General��m� -	   $ MenuItem_NewIn1��$��2D Animation��m� -
   $ MenuItem_NewIn2��$��	Sculpting��m� -   $ MenuItem_NewIn3��$	��VFX��m� -   $ MenuItem_NewIn4��$��Video Editing��m� -   $ MenuItem_Open��$��開く(_O)...��$ 	[Ctrl] O �� �� $&�� Images/FolderOpened_grey_16x.png��m� -   $ MenuItem_OpenRecent��$'��!最近使用したファイル...��$ [Shit][Ctrl] S ��m� -   $ MenuItem_Save��$��
保存(_S)��$ 	[Ctrl] S ��m� -   $ MenuItem_SaveAs��$%��名前をつけて保存(_A)...��$ [Ctrl Shift] S  ���� m� -   $ MenuItem_Append��$��アペンド...���� m� -   $ MenuItem_Import��$��インポート...��m� -   $ MenuItem_Export��$��エクスポート...���� m� -   $ MenuItem_Finalize��$��
終了(_Q)��$ [Ctrl] Q�� �� $��Images/Exit_16x.png��m� -   $ MenuItem_Edit��$��
編集(_E)��.@�m� -   $ MenuItem_Undo��$��元に戻す��$ [Ctrl] Z�� m� Command# Z  �� $��Images/Undo_16x.png��m� -   $ MenuItem_Redo��$��やり直す��$ [Ctrl] Y��# Z  �� $��Images/Redo_16x.png���� m� -   $ MenuItem_ZoomIn��$��拡大�� �� $��Images/ZoomIn_16x.png��m� -   $ MenuItem_ZoomOut��$��縮小�� �� $��Images/ZoomOut_16x.png���� m� -   $ MenuItem_Copy��$��	コピー�� �� $��Images/Copy_16x.png��m� -   $ MenuItem_Paste��$��貼り付け�� �� $��Images/Paste_16x.png��m� -   $ MenuItem_Help��$��ヘルプ(_H)��$ [Ctrl] H��.@�m� -   $ MenuItem_Version��$��バージョン情報(_A)���� $��1�� �� Orientation$ 
Horizontal=�$��0,0,-0.4,0.6q�
���   �.+��� -    ��Name$ Button_NewFile��$��10q���Z� ��Z� .���� $��Images/NewFile_16x.png���� -   $ Button_Open��$��10q���Z� ��Z� .���� $&�� Images/FolderOpened_Grey_16x.png���� -    $ Button_Undo��$��10q���Z� ��Z� .���� $��Images/Undo_16x.png���� -!   $ Button_Redo��$��10q���Z� ��Z� .���� $��Images/Redo_16x.png���� -"   $ Button_Zoom��$��10q���Z� ��Z� .���� $��Images/NewFile_16x.png���� -#   $ 
Button_zzz��$��10q���Z� ��Z� .���� $��Images/NewFile_16x.png���� -$   $��	ZoomLavel��$
��100%��$��40��$��Right=�$��Center=��� -%   ��Z� ��Z� .���� $��Images/ZoomOut_16x.png���� -&    ��Name$ Slider_Zoom��$��Center=�$	��160�� �� IsSnapToTickEnabled .  � Minimum$ 25Q� � Maximum$	 400Q� �� Ticks$&  25,50,75,100,125,150,200,300,400R� � Value$	 100Q�$��Center=��� -'   ��Z� ��Z� .���� $��Images/ZoomIn_16x.png��� $��1��$��0,30,-0.4,-0.4q�$��3�� � ColumnDefinitions �� �� $
��Auto ��� $	��200 �.+��� -(   $��scrollViewer��$��0��$
��Auto=�$
��Auto=���Z� ����  �� EndPoint$ 0.5,1&� �� 
StartPoint$ 0.5,0.0&�.���  � Color$ 	#FF8CECFF��� $ Black��  � Offset$	  0.1Q�� $ 	#FF8CECFF��$  1Q�� $ Black��$	  0.9Q�.���� -)   ! ��Name$! MainCanvas2��$	��640��$	��640��
���   �z�u� -*   matrixTransform���� $��1��$��4��$��Center=�$��Stretch=����� $ 0,0.0&�$ 0,1.0&�.��� $ 	#FF8CECFF��$	  0.9Q�� $ Black��� $ 	#FF8CECFF��$	  0.1Q�� $ Black��$  1Q�� $��2�� �� $
��Auto ��� $
��Auto ����� $ 0.5,1&�$ 0.5,0&�.��� $ 	#FF8CECFF��$  1Q�� $ Black��$	  0.1Q�� $ 	#FF8CECFF��$	  0.0Q�� $ Black��$	  0.9Q�.+��� $��0��$��カラーパレット��$��10q��� -+   " ��Name$" ColorPalette��$��1��$��30��$��
10,0,10,10q�
���   �
��������� $��3��$
��Left=�
��������� $��3��$
��Left=�
����������� $ 0.5,1&�$ 0.5,0&�.��� $ 	#FF8CECFF��$  1Q�� $ Black��$	  0.1Q�.@��� $��           ���� �� -,   $��StatusBarLabel��$	��aaa���� �� --   $��StatusBarLabel_Scale��$��拡大率：100%���� 