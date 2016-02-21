#include "Node.h"

std::string Node::getName(){
	return name;
}

std::string Node::getMac(){
	return macAdd;
}

void Node::handleInput(std::string data){

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
	writer.write();
}

void Node::localizeTwo(float baseDir){
	writer.write();
}

void Node::localizeThree(std::string macOne, std::string macTwo, float baseDir){
	writer.write();
}

std::tuple<float, float, std::string> Node::returnXYMac(){
	return std::make_tuple(x, y, macAdd);
}
