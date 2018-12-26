#include "Memory.h"
#include <iostream>
#include <vector>
#include "StringEditor.h"


Memory::Memory()
= default;



// add a variable to the list in form of an Object
void Memory::addVar(const std::string& name, const Object& o)
{
	nameLocations[name] = o;
	//std::cout << "added Variable: " << name << std::endl;
}

void Memory::addVar(const std::string& name, const int type, void* value)
{
	addVar(name, Object(type, value));
}

void Memory::addVar(const std::string& name, const Object& o, const std::string& scopeName)
{
	nameLocations[scopeName + '.' + name] = o;
}

void Memory::addVar(const std::string& name, const int type, void* value, const std::string& scopeName)
{
	addVar(name, Object(type, value), scopeName);
}
// ~~~~~~~~~~~~~~~~




// delete variable when its not needed anymore TODO test
void Memory::deleteVar(const std::string& name, const std::string& scopeName)
{
	// TODO make faster if possible & TEST
	for (int i = 0; i < getDeepestVar(name, scopeName).size(); i++)
		delete((char*)getDeepestVar(name, scopeName).location + i);
	nameLocations.erase(name);
}




// get a variable in form of an Object by a given name
Object Memory::getVar(const std::string& name)
{
	return nameLocations[name];
}

Object Memory::getVar(const std::string& name, const std::string& scopeName)
{
	return getDeepestVar(name, scopeName);
}
// ~~~~~~~~~~~~~~~~~~~~




// get the location of the value of a variable by a given name
void* Memory::getLocation(const std::string& name, const std::string& scopeName)
{
	return getDeepestVar(name, scopeName).location;
}


// get the type of the value of a variable by a given name
int Memory::getType(const std::string& name, const std::string& scopeName)
{
	return getDeepestVar(name, scopeName).type;
}


// returns the "closest" variable in form of an Object by a given name
// cecks if var exists in current scope, if true -> return, if false -> check in outer scope
Object Memory::getDeepestVar(const std::string& name, std::string scopeName)
{
	Object var = getVar(scopeName + '.' + name);
	while (!var.exists())
	{
		const size_t snindex = scopeName.rfind('.');
		scopeName = scopeName.substr(0, snindex);
		var = getVar(scopeName + '.' + name);
	}
	return var;
}

// like getDeepestVar but returns the name not the var
std::string Memory::getDeepestName(const std::string& name, std::string scopeName)
{
	Object var = getVar(scopeName + '.' + name);
	while (!var.exists())
	{
		const size_t snindex = scopeName.rfind('.');
		scopeName = scopeName.substr(0, snindex);
		var = getVar(scopeName + '.' + name);
	}
	return scopeName + '.' + name;
}



std::vector<std::string> Memory::getFuncHeader(const std::string& fullName)
{
	return functionHeaders[fullName];
}

std::vector<std::string> Memory::getFuncHeader(const std::string& name, const std::string& scopeName)
{
	return getFuncHeader(scopeName + '.' + name);
	//return functionHeaders[getDeepestName(name, scopeName)];
}

void Memory::addFuncHeader(const std::string& name, const std::string& scopeName, const std::vector<std::string>& header)
{
	functionHeaders[scopeName + '.' + name] = header;
}

std::vector<std::string> Memory::getFuncInits(const std::string& name, const std::string& scopeName)
{
	return functionInits[scopeName + '.' + name];
}

void Memory::addFuncInit(const std::string& name, const std::string& scopeName, const std::vector<std::string>& value)
{
	functionInits[scopeName + '.' + name] = value;
}

//void Memory::addFuncHeader(const std::string& name, const std::string& scopeName, const std::string& header)
//{
//	std::string varNames;
//	std::vector<std::string> inits = StringEditor::split(header, ',');
//	for (const std::string& init : inits)
//	{
//		varNames.append(init.substr(init.find(' ')+1)).append(",");
//	}
//	functionHeaders[scopeName + '.' + name] = varNames;
//}



std::string Memory::getScopeName(const std::string& varName)
{
	return varName.substr(0, varName.rfind('.'));
}