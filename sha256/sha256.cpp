#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

class CPadding
{
public:
	
	int handleLength = 0;
	int handleBits = 0;
	int handleBlocks = 0;
	int handleSwitch = 0;
	unsigned char block[64];

	void StringCalc(std::string input)
	{
		handleLength = input.length();
		handleBits = handleLength * 8;
		handleBlocks = handleBits / 512;
		handleSwitch = 0; // laatste blok 448 512
		if (handleBits % 512 != 0)
		{
			++handleBlocks;
		}
		handleSwitch = 0; // laatste blok 448 512
	}

	void BlockCalc(std::string input)
	{
		for (int i = 0; i < handleBlocks; i++)
		{
			// laaste blok
			if (i == handleBlocks - 1)
			{
				for (int j = (i * 64); j < input.length(); ++j)
				{
					block[j - (i * 64)] = input[j];			
				}
				for (int j = (input.length()); j < ((i+1) * 64); ++j) //rest laatste blok, laatste totaal in hex + 448 regel
				{
					if (j == input.length())
					{
						block[j - (i * 64)] = 0x80;
					}
					else
					{
						block[j - (i * 64)] = 0x00;
					}					
				}
			}
			else
			{
				for (int j = (i * 64); j < ((i + 1) * 64); ++j)
				{
					block[j - (i * 64)] = input[j];
				}
			}
			// => hier calculatie blokken
			this->ProcessBlock();
		}
	}

	void ProcessBlock()
	{
		for (int g = 0; g < 64; g++)
		{
			std::cout << std::hex << std::setfill('0') << std::setw(2) << unsigned int(block[g]);
			if (((g + 1) % 4 == 0) && ((g + 1) % 32 != 0))
			{
				std::cout << " ";
			}
			if ((g + 1) % 32 == 0)
			{
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}

};


int main()
{
	using namespace std;
	
	string sString1 = "abc";
	string sString2 = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"; // 448 blok
	string sString3 = "Lorem ipsum is opvultekst wat bedoeld is om de indruk van echte woorden en zinnen te geven. In tegenstelling tot het herhalen van dezelfde opvulwoorden heeft lorem ipsum een goede afwisseling van verschillende letters en korte- en lange woorden en zinnen.";
	string sString4 = "Het is al geruime tijd een bekend gegeven dat een lezer, tijdens het bekijken van de layout van een pagina, afgeleid wordt door de tekstuele inhoud. Het belangrijke punt van het gebruik van Lorem Ipsum is dat het uit een min of meer normale verdeling van letters bestaat, in tegenstelling tot Hier uw tekst, hier uw tekst wat het tot min of meer leesbaar nederlands maakt. Veel desktop publishing pakketten en web pagina editors gebruiken tegenwoordig Lorem Ipsum als hun standaard model tekst, en een zoekopdracht naar lorem ipsum ontsluit veel websites die nog in aanbouw zijn. Verscheidene versies hebben zich ontwikkeld in de loop van de jaren, soms per ongeluk soms expres (ingevoegde humor en dergelijke).";
	string sString5 = "Er zijn vele variaties van passages van Lorem Ipsum beschikbaar maar het merendeel heeft te lijden gehad van wijzigingen in een of andere vorm, door ingevoegde humor of willekeurig gekozen woorden die nog niet half geloofwaardig ogen. Als u een passage uit Lorum Ipsum gaat gebruiken dient u zich ervan te verzekeren dat"; // 512 blok
	
	CPadding x;
	
	x.StringCalc(sString4);
	cout << "Length: " << x.handleLength << endl;
	cout << "Bits: " << x.handleBits << endl;
	cout << "Blocks: " << x.handleBlocks << endl;

	// doorloop alle blokken
	x.BlockCalc(sString4);
	
	return 0;
}

