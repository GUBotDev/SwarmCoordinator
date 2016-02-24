#include "DecisionHandler.h"

Node DecisionHandler::node;
//bool DecisionHandler::initComp = false;

void DecisionHandler::setBeacons(float* x, float* y, std::string* ID, int numBeacons){
	node.setBeacons(x, y, ID, numBeacons);
	beaconsInitialized = true;
}

void DecisionHandler::move(float x, float y){
	/*
	if (node.getBeacon() <= 3 && node.getBeacon() >= 1){
		node.moveToPosition(x, y, , );
	}
	else 
	*/
	if (initComp && beaconsInitialized){
		std::pair<float, float> tempPos = node.returnXY();
		node.moveToPosition(x, y, tempPos.first, tempPos.second);
		node.checkTolerances(x, y, tempPos.first, tempPos.second);
	}
	else{
		node.initialize();
		node.requestBeacons();
	}
}

void DecisionHandler::turn(float targetDirection){
	if (initComp && beaconsInitialized){
		node.turnTo(targetDirection);
		node.checkTolerances(targetDirection);
	}
	else{
		node.initialize();
		node.requestBeacons();
	}
}

void DecisionHandler::localize(int num, float direction, std::string macOne, std::string macTwo){
	//if (initComp && beaconsInitialized){
		switch(num){
			case 1:
				node.locateOne();
				node.setBeacon(1);
				break;
			case 2:
				node.locateTwo(direction);
				node.setBeacon(2);
				break;
			case 3:
				node.locateThree(macOne, macTwo, direction);
				node.setBeacon(3);
				break;
		}
	/*}
	else{
		node.initialize();
		node.requestBeacons();
	}*/
}

void DecisionHandler::initialize(){
	node.initialize();
}

void DecisionHandler::initComplete(){
	initComp = true;
}

bool DecisionHandler::isInit(){
	return initComp;
}

void DecisionHandler::alreadyInitialized(){
	node.alreadyInitialized();
}

void DecisionHandler::sendPosDir(){
	node.sendLastPositionDirection();
}

void DecisionHandler::unknownCommand(std::string data){
	node.unknownCommand(data);
}


