
#ifndef _TEXTCONSOLE_H_
#define _TEXTCONSOLE_H_

#include "JuceHeader.h"

class TextConsole : public TextEditor {

public:
	TextConsole() : TextEditor("Console") {
		setMultiLine(true);
		setReadOnly(true);
	}
	void addLine(const String& text) {
		setCaretPosition(getText().length());
		insertTextAtCaret(text);
	}
private:

};

#endif//_TEXTCONSOLE_H_