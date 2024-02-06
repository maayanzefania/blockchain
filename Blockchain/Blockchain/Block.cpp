#include "Block.h"

Block::Block(Header head, std::string prev)
{
	_header = head;
	_prevHash = prev;
	
	
}

Block::Block(std::string str)
{
	std::vector<std::string> info = FileManager::splitString(str, BLOCK_DELIMETER);
	_header.nonce = std::stoi(info[NONCE]);
	_header.targetHash = info[TARGET];
	_header.timestamp = std::stoll(info[TIMESTAMP]);
	_header.version = std::stof(info[VERSION]);
	_prevHash = info[PREV];
	if (info.size() != 5)
	{
		std::vector<std::string> transactions = FileManager::splitString(info[info.size() - 1], TRANSACTION_DELI);
		for (int i = 0; i < transactions.size(); i++)
		{
			Transaction* t = new Transaction(transactions[i]);
			if (!addTransaction(t))
			{
				throw(std::exception());
			}
		}
	}
	
	
}


std::string Block::append()
{
	std::string block_str = std::to_string(this->_header.nonce) + BLOCK_DELIMETER + this->_header.targetHash + BLOCK_DELIMETER + std::to_string(this->_header.timestamp) + BLOCK_DELIMETER + std::to_string(this->_header.version) + BLOCK_DELIMETER + this->_prevHash;
	if (_data.size() != 0)
	{
		block_str += BLOCK_DELIMETER;
	}
	for (int i = 0; i < this->_data.size(); i++)
	{
		block_str += this->_data[i]->toString();
		if (i != this->_data.size() - 1)
		{
			block_str += TRANSACTION_DELI;
		}
	}
	return block_str;
}

Block::~Block()
{
	for (int i = 0; i < _data.size(); i++)
	{
		delete _data[i];
	}
}

bool Block::addTransaction(Transaction* transaction)
{
	if (_data.size() < MAX)
	{
		_data.push_back(transaction);
		return true;
	}
	return false;
	
}

bool Block::operator==(Block& other)
{
	if (this->_header.version != other._header.version)
	{
		return false;
	}
	if (this->_header.timestamp != other._header.timestamp)
	{
		return false;
	}
	if (this->_header.version != other._header.version)
	{
		return false;
	}
	if (this->_prevHash != other._prevHash)
	{
		return false;
	}
	if (this->_data != other._data)
	{
		return false;
	}
	return true;
}

std::string Block::getPrev()
{
	return _prevHash;
}




bool Block::mine()
{
	std::string rawData = append();
	std::string hash = SHA256::conv(rawData);
	//if()
	return false;
}

