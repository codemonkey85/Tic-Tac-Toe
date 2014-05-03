#pragma once

namespace TTT_CLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			port = 9999;
			ipAddress = Dns::GetHostEntry(Dns::GetHostName())->AddressList[0];
			ipEndpoint = gcnew IPEndPoint(ipAddress, port);
			listenerSocket = gcnew Socket(ipAddress->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
			listenerSocket->Bind(ipEndpoint);

			// create a new thread to run the server			
			serverThread = gcnew Thread(gcnew ThreadStart(this, &Form1::runServer));
			serverThread->Start();
		}

	public:
		void runServer()
		{
			stopRequested = false;
			listenerSocket->Listen(2);
			richTextBox1->Text = richTextBox1->Text + "Waiting for client connections...";
			int count = 1;
			listenerSocket->Blocking = false;
			while (!stopRequested){
				try{
					Socket^ serverSocket = listenerSocket->Accept();
					serverSocket ->Blocking = true;
					if (stopRequested) break;
					richTextBox1 ->Text = richTextBox1 ->Text + "\nNew connection accepted";
					Service^ service = gcnew Service(serverSocket, this);
					Thread^ childThread = gcnew Thread(gcnew ThreadStart(service, &Service::DoService));
					childThread->Name = "t" + count;
					childThread->Start();
					count++;
				}
				catch(SocketException^ e){
					Thread::Sleep(200);
				}
			}
			richTextBox1 ->Text = richTextBox1 ->Text +"Server stopped.\n";
			btnClose ->Enabled = true;
			btnStop ->Enabled = false;
			if(serverSocket != nullptr){
				serverSocket->Shutdown(SocketShutdown::Both);
				serverSocket->Close();
			}
		} // end RunServer
		ref class Service
		{
		private: Socket^ serverSocket;
				 Form1^ theForm;
				 NetworkStream^ netStream;
				 BinaryReader^ br;
				 BinaryWriter^ bw;
		public: Service(Socket^ aSocket, Form1^ form)
				{
					serverSocket = aSocket;
					theForm = form;
					netStream = gcnew NetworkStream(serverSocket);
					br = gcnew BinaryReader(netStream);
					bw = gcnew BinaryWriter(netStream);
				}
				void DoService()
				{
					String^ threadName = Thread::CurrentThread->Name;
					bw -> Write("\n" + threadName + ": Client connected.");
					try {
						int value1, value2;
						int result;
						while (true) //until end of input
						{
							value1 = br->ReadInt32();						
							value2 = br->ReadInt32();						
							result = value1 + value2;
							theForm->richTextBox1->Text = theForm->richTextBox1->Text+ threadName + 
								": received: " + value1 + ", " + value2+ "; sending: " + result + "\n";
							bw->Write(result);						
						}
					}
					catch (EndOfStreamException^ e)
					{ //client finished
						theForm->richTextBox1->Text = theForm->richTextBox1->Text+threadName + ": Client disconnected\n";
						netStream->Close();
					}

				} // end DoService
		}; // end class Service

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		int port;
		IPAddress^ ipAddress;
		IPEndPoint^ ipEndpoint;
		Socket^ listenerSocket;
		Socket^ serverSocket;		
		Thread^ serverThread;
		bool stopRequested; //to end the serverThread loop

	private: System::Windows::Forms::Button^  btnStop;
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::VScrollBar^  vScrollBar1;
			 /// <summary>
			 /// Required designer variable.
			 /// </summary>
			 System::ComponentModel::Container ^components;
#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
	private: void InitializeComponent(void) {
				 this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
				 this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
				 this->SuspendLayout();
				 // 
				 // richTextBox1
				 // 
				 this->richTextBox1->BackColor = System::Drawing::SystemColors::ScrollBar;
				 this->richTextBox1->Location = System::Drawing::Point(8, 9);
				 this->richTextBox1->Name = L"richTextBox1";
				 this->richTextBox1->Size = System::Drawing::Size(269, 244);
				 this->richTextBox1->TabIndex = 0;
				 this->richTextBox1->Text = L"";
				 // 
				 // vScrollBar1
				 // 
				 this->vScrollBar1->Location = System::Drawing::Point(259, 9);
				 this->vScrollBar1->Name = L"vScrollBar1";
				 this->vScrollBar1->Size = System::Drawing::Size(17, 244);
				 this->vScrollBar1->TabIndex = 1;
				 // 
				 // Form1
				 // 
				 this->ClientSize = System::Drawing::Size(284, 262);
				 this->Controls->Add(this->vScrollBar1);
				 this->Controls->Add(this->richTextBox1);
				 this->Name = L"Form1";
				 this->Text = L"Tic Tac Toe Server";
				 this->ResumeLayout(false);

			 }
#pragma endregion
	};//end Form1

	/*
	public class Person
	{
	internal: Socket^ connection;
	private: NetworkStream^ socketStream;
	private: Server^ server;
	private: BinaryWriter^ writer;
	private: BinaryReader^ reader;

	private: int number;
	private: char mark;
	internal: Bool^ threadSuspended = true;

	// constructor requiring Socket, Server and int objects as arguments
	public: Player(Socket socket, Server serverValue, int newNumber)
	{
	mark = (newNumber == 0 ? 'X' : 'O');
	connection = socket;
	server = serverValue;
	number = newNumber;

	//network stream object for Socket
	socketStream = gcnew NetworkStream(connection);

	//streams for writing/reading bytes
	writer = gcnew BinaryWriter(socketStream);
	reader = gcnew BinaryReader(socketStream);
	}
	public: 
	void otherPlayerMoved(int location)
	{
	//signal move
	writer->write("Opponent moved:");
	writer->write(location);
	}
	//player makes moves/receives moves from other player
	public:
	void Run()
	{
	bool done = false;
	server->Display("Player " + (number == 0 ? 'X' : 'O') + " connected.");
	}
	}
	*/
}//end namespace


