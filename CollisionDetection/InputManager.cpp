#include "InputManager.h"

InputManager::InputManager(){
	oldKeyState = new int[256];
	keyState = new int[256];
	for (int i = 0; i < 256; i++){
		oldKeyState[i] = 1;
		keyState[i] = 1;
	}
}

InputManager::~InputManager(){

	return;
}

void InputManager::Update(){
	int* swap;
	swap = oldKeyState;
	oldKeyState = keyState;//new is now old
	keyState = swap;//old becomes new, but will be overwritten right now

	for (int i = 0; i < 256; i++){
		keyState[i] = GetAsyncKeyState(i) & 0x8000 ? 2 : 1;
	}
}

bool InputManager::IsKeyDown(char c){
	//return keyState[c];
	if (keyState[c] == 2){
		return true;
	}
	else return false;
}

bool InputManager::IsKeyDownEx(char c){
	if (keyState[c] == 2 && oldKeyState[c] != 2){
		return true;
	}
	else return false;
}
