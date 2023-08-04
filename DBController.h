#include "pch.h"
#include <sql.h>
#include <sqlext.h>

#pragma once
class DBController
{
public:
	bool db_connect();
	void db_disconnect();
	const char* get_data_type_in_string(SQLSMALLINT dataType);
	const char* dataSourceName = "DB01_Server";
	const char* serverId = "KIM";
	const char* serverPw = "1234";
	SQLHENV hEnv = NULL;	// Environment Handle
	SQLHDBC hDbc = NULL;	// Connection Handle

public:
	CString hello();
};

