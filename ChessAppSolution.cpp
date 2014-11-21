// ChessAppSolution.cpp : Defines the entry point for the console application.

#include "ChessDll.h"
#include "stdafx.h"
#include <string>
#include <sstream>			// stringstream
#include <vector>
#include <fstream>			// filestream
#include <iostream>			// cout
#include <algorithm>		// remove_if
#include <cmath>

using namespace std ;

void displayGame( ChessBoard myBoard )
{
	vector <char> temp = myBoard.getBoard( ) ;
	std::cout << "\n\n\n" ;
	int k = 8 ;
	for( int i = temp.size( ) - 1 ; i >= 0 ; i -= 8 )
	{
		cout << k-- << "\t" ; 
		for( int j = i - 7 ; j <= i ; j++ )
			std::cout << temp.at( j ) << "\t" ;
		cout << "\n\n\n\n\n" ;
	}
	cout << "\n\ta\tb\tc\td\te\tf\tg\th\n\n\n\n" ;
}

vector<string> &split( const string &s , char delim , vector<string> &elems ) 
{
    stringstream ss ( s ) ;
    string item ;
    while ( getline ( ss , item , delim ) ) {
		if ( item != "" )
			elems.push_back ( item ) ;
    }
    return elems ;
}

vector<string> split( const string &s , char delim ) 
{
    std::vector<std::string> elems ;
    split( s , delim , elems ) ;
    return elems ;
}

int main( ) {
	ifstream myfile ( "D:\\MalakaGL\\Chess\\game6.txt" ) ;
	//ifstream myfile ( "E:\\Training\\ChessApplication\\game.txt" ) ;
	ChessBoard myBoard ;
	string line ;

	displayGame( myBoard ) ;

	if ( myfile.is_open( ) )
	{
		int lineNumber = 0 ;
		while ( getline ( myfile , line ) )
		{
			lineNumber++ ;
			vector <string> temp = split ( line , ' ' ) ;
			if( myBoard.getWinner( ) == EMPTY )
			{
				if( temp.size( ) < 3 )
				{
					break ;
				}

				temp.at( 1 ).erase( remove_if( temp.at( 1 ).begin( ) , temp.at( 1 ).end( ) , isspace ) , temp.at( 1 ).end( ) ) ;
				temp.at( 2 ).erase( remove_if( temp.at( 2 ).begin( ), temp.at( 2 ).end(), isspace), temp.at(2).end());
				
				if ( myBoard.isValid(temp.at(1)))
				{
					myBoard.move( temp.at( 1 ) ) ;
					displayGame( myBoard ) ;
				}
				else
				{
					cout << "\nErrorneous move by white player at line " << lineNumber << "\n" << temp.at( 1 ) ;
					break ;
				}
				if ( myBoard.isValid( temp.at( 2 ) ) )
				{
					myBoard.move( temp.at( 2 ) ) ;
					displayGame( myBoard ) ;
				}
				else
				{
					cout << "\nErrorneous move by black player at line " << lineNumber << "\n" << temp.at( 2 ) ;
					break ;
				}
			}
			else
			{
				char winColor = myBoard.getWinner( ) ;
				string winner = ( winColor == WHITE ) ? "White" : "Black" ;
				cout << "Game won by : " << winner ;
			}
		}
		myfile.close( ) ;
	} else 
	{
		cout << "Unable to open file" ; 
	}

	cout << "\nFinal state of the board.\n\n" ;
	displayGame( myBoard ) ;

	return 0 ;
}