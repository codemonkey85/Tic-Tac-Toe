#pragma once
//#include "Square.h"


namespace TTT_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;
	using namespace System::IO;

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
		}

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
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		int port;
		int messageCount;
		IPAddress^ ipAddress;
		IPEndPoint^ ipEndpoint;
		Socket^ clientSocket;		
		NetworkStream^ netStream;
		BinaryReader^ reader;
		BinaryWriter^ writer;
	private: System::Windows::Forms::RichTextBox^  lblOut;
	private: System::Windows::Forms::Button^  ConnectBtn;
			 

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ConnectBtn = (gcnew System::Windows::Forms::Button());
			this->lblOut = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// ConnectBtn
			// 
			this->ConnectBtn->Location = System::Drawing::Point(16, 9);
			this->ConnectBtn->Name = L"ConnectBtn";
			this->ConnectBtn->Size = System::Drawing::Size(76, 25);
			this->ConnectBtn->TabIndex = 0;
			this->ConnectBtn->Text = L"Connect";
			this->ConnectBtn->UseVisualStyleBackColor = true;
			this->ConnectBtn->Click += gcnew System::EventHandler(this, &Form1::ConnectBtn_Click);
			// 
			// lblOut
			// 
			this->lblOut->Location = System::Drawing::Point(14, 47);
			this->lblOut->Name = L"lblOut";
			this->lblOut->Size = System::Drawing::Size(256, 23);
			this->lblOut->TabIndex = 1;
			this->lblOut->Text = L"";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->lblOut);
			this->Controls->Add(this->ConnectBtn);
			this->Name = L"Form1";
			this->Text = L"Tic Tac Toe Client";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ConnectBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		try{
			port = 9999;
			messageCount = 3;
			ipAddress = Dns::GetHostEntry(Dns::GetHostName())->AddressList[0];
			ipEndpoint = gcnew IPEndPoint(ipAddress, port);
			clientSocket = gcnew Socket(ipAddress ->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
			//lblOut->Text = lblOut->Text + "Client sending connection request.\n"; 
			clientSocket->Connect(ipEndpoint);
			netStream = gcnew NetworkStream(clientSocket);		
			reader = gcnew BinaryReader(netStream);
			writer = gcnew BinaryWriter(netStream);			
			ConnectBtn ->Enabled = false;
			String^ confirmation = reader ->ReadString();
			lblOut ->Text = lblOut->Text + confirmation+ "\n";			
			//btnSend ->Enabled = true;
			//btnTerminate ->Enabled = true;
		}
		catch (SocketException^ e) {
          lblOut->Text =("Request to connect to {0} on port {1} failed"
                            + "\nbecause of {2}\n", ipAddress, port, e->ToString());
          Environment::Exit(5);
			 }
	}
};
}

