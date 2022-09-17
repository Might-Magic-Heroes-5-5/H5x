#define EXPORT __declspec(dllexport)
#define EXPORTC extern "C" __declspec(dllexport)

extern void main();

// This class is exported from the dll
class EXPORT CH5DLL {
public:
	CH5DLL(void);
	// TODO: add your methods here.
};

extern EXPORT int nH5DLL;

EXPORT int fnH5DLL(void);
