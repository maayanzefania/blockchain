#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <array>
#define SIZE 4
#define HEX 16
class AES
{
public:
	AES();
	~AES();
	void encrypt(unsigned char** state, unsigned char** key);
	void decrypt(unsigned char** state, unsigned char** key);
	void GKey(unsigned char** state);
private:
    static const unsigned char sbox[HEX][HEX];

	static const unsigned char inv_sbox[HEX][HEX];

	static const unsigned char CMDS[4][4];

	static const unsigned char INV_CMDS[4][4];
	void AddRoundKey(unsigned char** state, unsigned char** key);
	void ShiftRow(unsigned char** state, unsigned int i, unsigned int n);
	void ShiftRows(unsigned char** state);
	void SubBytes(unsigned char** state);
	void SubBytes(unsigned char* state);
	void InvShiftRows(unsigned char** state);
	void InvSubBytes(unsigned char** state);
	void InvMixColumns(unsigned char** state);
	void MixColumns(unsigned char** state);
	int getRcon(int round);
	void keyExpansion(unsigned char** key, int round);
	int aesMul(int a, int b);
};

