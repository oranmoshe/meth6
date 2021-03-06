#include "TextBox.h"

TextBox::TextBox(int width) : Control(width) {
	_cursor = { GetLeft() + getText().length() + 1, getTop() + 1 };

}

TextBox::~TextBox() {

}

void TextBox::draw(Graphics& g, int x, int y, size_t layer) {
	Control::draw(g, x, y, layer);
	if (getBorder() != BorderType::None) g.write(GetLeft() + 1, getTop() + 1, getText()); //draw the textbox
	else {
		g.write(GetLeft(), getTop(), getText());
	}
}

bool TextBox::isCursorable(){
	return true;
}
//handle the mouse event
void TextBox::mousePressed(int x, int y, bool isLeft) {
	if (isClicked(x, y) && y - 1 == getTop() && x > GetLeft()){  //Checking if pressed on one of the letters of the word
		this->_cursor.X = x;
		this->_cursor.Y = y;
	}
	if (isClicked(x, y) && y - 1 == getTop() && x > GetLeft() + this->getText().length())  //if the user click where there is no string the cursor will be in the end of the word
	{
		this->_cursor.X = GetLeft() + this->getText().length() + 1;
		this->_cursor.Y = y;
	}
}
//handle the keyword input
void TextBox::keyDown(int code, char ch) {
	COORD crd;
	crd.Y = _cursor.Y;
	crd.X = _cursor.X;
	Graphics().moveTo(this->_position.X + 1, this->_position.Y + 1);

	if ((code >= 65 && code <= 90) || (code >= 97 && code <= 122) || (code >= 48 && code <= 57) || (code == 32)) // check if the char is the char that can written in the textbox
	{
		if (_cursor.X == this->getText().length() + this->_position.X + 1)			//write the input char
		{
			if (this->getText().length() < this->_position.X - 6 || this->getText().length() == this->_position.X - 6)
			{
				string a = this->getText() + string(1, ch);
				this->setText(a);							//add the char to the value of the control
				crd.X++;
				_cursor = (crd);
			}
		}
		else
		{
			if (this->getText().length() < this->_position.X - 6 || this->getText().length() == this->_position.X - 6)
			{
				string a = this->getText();
				int index = _cursor.X - this->_position.X - 1;
				a.insert(index + 1, std::string(1, ch));
				this->setText(a);
				crd.X++;
				_cursor = (crd);
			}
		}
	}
	COORD coord;
	string temp;
	coord.Y = _cursor.Y;
	switch (code){
	case VK_BACK:
		if (_cursor.X>this->_position.X + 1)
		{
			coord.X = _cursor.X - 1;
			_cursor = (coord);
			temp = getText();
			temp.erase(coord.X - _position.X - 1, 1);
			setText(temp);
		}
		break;
	case VK_RIGHT:
	case VK_NUMPAD6:
		temp = getText();
		if (_cursor.X< this->_position.X + this->getText().length() + 1)
		{
			coord.X = _cursor.X + 1;
			_cursor = (coord);
		}
		break;
	case VK_LEFT:
	case VK_NUMPAD4:
		if (_cursor.X>this->_position.X + 1)
		{
			coord.X = _cursor.X - 1;
			_cursor = (coord);
		}
		break;
	case VK_RETURN:
		break;
	case VK_DELETE:
		coord.X = _cursor.X - 1;
		temp = getText();
		if (coord.X <temp.length() + _position.X)
		{
			temp.erase(coord.X - 1 - _position.X + 1, 1);
		}
		setText(temp);
		break;
	default:
		break;
	}
}

bool TextBox::canGetFocus() const {
	return true;
}
//clear the char from the console
void TextBox::clear(){
	for (int i = this->_position.X; i < this->_position.X + this->getText().length(); i++){
		setCursor(i, this->_position.Y);
		printf("%c", ' ');
	}
}