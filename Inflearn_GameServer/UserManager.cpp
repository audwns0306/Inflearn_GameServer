#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

void UserManager::ProcessSave()
{
	std::lock_guard<std::mutex> guard(_mutex);

	Account* account = AccountManager::Instance()->GetAccount(100);

	// TODO
}