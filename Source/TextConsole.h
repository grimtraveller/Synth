
#ifndef _TEXTCONSOLE_H_
#define _TEXTCONSOLE_H_

#include "JuceHeader.h"

class TextConsole : public TextEditor {

public:
	TextConsole() : TextEditor("Console") {
		setMultiLine(true);
		setReadOnly(true);
		index = 0;
	}
	void addLine(const String& text) {
		index++;
		setCaretPosition(getText().length());
		insertTextAtCaret(std::to_string(index) + ": " + text);
	}
private:
	int index;
};

#endif//_TEXTCONSOLE_H_