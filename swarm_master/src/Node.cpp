#include "Node.h"

std::string Node::getName(){
	return name;
}

std::string Node::getMac(){
	return macAdd;
}

void Node::setBeacon(bool hasBeacon){
	this->hasBeacon = hasBeacon;
}

void Node::setBusy(bool isBusy){
	this->isBusy = isBusy;
}

void Node::setName(std::string name){
	this->name = name;
}

void Node::setAddress(std::string address){
	this->macAdd = address;
}

void Node::localizeOne(){
	std::string concat = name + " localize 1";

	writer.write(concat);
}

void Node::localizeTwo(float baseDir){
	std::string concat = name + " localize 2 " + std::to_string(baseDir);

	writer.write(concat);
}

void Node::localizeThree(std::string macOne, std::string macTwo, float baseDir){
	std::string concat = name + " " + macOne + " " + macTwo + " " + std::to_string(baseDir);

	writer.write(concat);
}

std::tuple<float, float, std::string> Node::returnXYMac(){
	return std::make_tuple(x, y, macAdd);
}

void Node::setXYD(float x, float y, float direction){
	this->x = x;
	this->y = y;
	this->direction = direction;
}

void Node::moveToPosition(float x, float y, float dir){
	std::string concat = name + " move " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(dir);
	
	writer.write(concat);
}

void Node::turn(float direction){
	std::string concat = name + " turn " + std::to_string(direction);
	
	writer.write(concat);
}

void Node::returnPosition(){
	std::string concat = name + " return_position";
	
	writer.write(concat);
}

void Node::wait(){
	std::string concat = name + " wait";
	
	writer.write(concat);
}



