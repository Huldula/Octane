#define INT 0
#define LONG 1
#define FLOAT 2
#define DOUBLE 3
#define BOOL 4
#define CHAR 5
#define SHORT 6
#define FUNC 7

#define SWITCH(varName, command, other) switch(varName) { \
	case INT: \
		command(int) \
		break; \
	case LONG: \
		command(long) \
		break; \
	case FLOAT: \
		command(float) \
		break; \
	case DOUBLE: \
		command(double) \
		break; \
	case CHAR: \
		command(char) \
		break; \
	case SHORT: \
		command(short) \
		break; \
	other \
	}

#define EMPTY break;

#define VAR_NAME std::string("[a-zA-Z_]\\w*")