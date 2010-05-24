
#pragma once


struct QQMESSAGE
{
	char Sender[100];
	char Time[9];
	char * message;
};


bool parsemessage ( const char * message);

