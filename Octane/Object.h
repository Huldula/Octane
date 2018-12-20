#pragma once

class Object
{
public:
	Object();
	Object(int type_, void* location_);
	~Object();
	int type;
	void* location;
	int size() const;
	bool exists() const;
};

