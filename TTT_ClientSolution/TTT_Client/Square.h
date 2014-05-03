//Square on the board for the client

using namespace System::Windows::Forms;

namespace TTT_Client
{
public ref class Square
		{
		private: Panel panel;
		private: char mark;
		private: int location;

		//constructor
		public: Square(Panel newPanel, char newMark, int newLocation)
				{
					panel = newPanel;
					mark = newMark;
					location = newLocation;
				}
		public: Panel SquarePanel
				{
					void get_panel()
					{
						return panel;
					}
				}
		public: char Mark
				{
					void get_mark()
					{
						return mark;
					}
					void set_mark()
					{
						mark = value;
					}
				}
		public: int Location
				{
					get_location()
					{
						return location;
					}
				}
		};
}