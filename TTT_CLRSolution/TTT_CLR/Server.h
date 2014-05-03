// Fig. 22.7: Server.cs
// This class maintains a game of Tic-Tac-Toe for two
// client applications.

typedef unsigned char byte;

using namespace System;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::IO;

namespace TicTacToeServer
{

	ref class Player;
	ref class Server;

}

/*
**************************************************************************
* (C) Copyright 2002 by Deitel & Associates, Inc. and Prentice Hall.     *
* All Rights Reserved.                                                   *
*                                                                        *
* DISCLAIMER: The authors and publisher of this book have used their     *
* best efforts in preparing the book. These efforts include the          *
* development, research, and testing of the theories and programs        *
* to determine their effectiveness. The authors and publisher make       *
* no warranty of any kind, expressed or implied, with regard to these    *
* programs or to the documentation contained in these books. The authors *
* and publisher shall not be liable in any event for incidental or       *
* consequential damages in connection with, or arising out of, the       *
* furnishing, performance, or use of these programs.                     *
**************************************************************************
*/
