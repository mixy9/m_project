#include "Application.h"
#include "main.h"



int main()
{
	Application application;
	if (!application.initialize())
		return EXIT_FAILURE;
	return application.execute();
}


