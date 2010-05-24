

#include "parse.h"
#include "eval_r.h"

#include <stdio.h>


int main(int argc, char * argv[])
{
	
	float f;
	
	if (argc != 2)
	{
		printf("input express to test parse().");
	}else{		
		char *p =parse(argv[1]);
		if (p==NULL)
		{
			printf("Invalid Express.");
		}else{
			//printf(p);
			//return 0;
			if (eval_r(p,&f))
			{
				printf("%s=%d", p, int(f));
			}else{
				printf("eval error.");
			}
		}
	}
	
	return 0;
	
}

