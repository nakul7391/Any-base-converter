/*This program is to take input from command line and convert given number to any number system */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// print the usage information
void print_usage()
{
		printf("[OPTION] ..[NUMBER] [BASE]\n");
		printf("Convert number to different formats\n\n");
		printf("    --help     Display this help and exit\n");
		printf("-d, --decimal  Convert number to decimal format\n");
		printf("-b, --binary   Convert number to binary format\n");
		printf("-o, --octal    Convert number to octal format\n");
		printf("-h, --hex      Convert number to hexadecimal format\n");
}

// function to validate input
int validate_input(char *num, char *base);

// function to convert given number to decimal
int convert_to_decimal(char *num, char *base);

/* main function*/
int main(int argc, char *argv[] )
{
		/*parse input options*/
		int opt = 0;

		/*long option structure*/
		static struct option long_options[] = {
				{"help",	  no_argument,	          NULL,	   'u' },
				{"decimal",	required_argument,			NULL,	   'd' },
				{"binary",	required_argument,	    NULL,	   'b' },
				{"octal",	  required_argument,			NULL,	   'o' },
				{"hex",	    required_argument,			NULL,	   'h' },
				{0,0,0,0},
			};

			if(argc > 1)
			{
				if (validate_input(argv[2],argv[3]) == 0)
				{
						printf("Invalid number\n");
						exit(0);
				}
			}


			int long_index = 0;
			/*parse command line inputs*/
			while ((opt = getopt_long(argc, argv,"ud:b:o:h:",long_options, &long_index )) != -1)
	 		{
		  	switch (opt)
		  	{
					  case 'u' : print_usage();
											 break;
						case 'd' : printf("Decimal %d\n", convert_to_decimal(argv[optind-1], argv[optind]));
											 break;
						case 'o' : printf("Octal %o\n", convert_to_decimal(argv[optind-1], argv[optind]));
											 break;
						case 'h' : printf("Hexadecimal %#X\n", convert_to_decimal(argv[optind-1], argv[optind]));
											 break;
					  default: /*error message is already showed exit the program*/
										exit(0);
			   }

			 }

			return 0;
}


int convert_to_decimal(char *num, char *base)
{
		int dec = 0, base_int = 1, i = 0, len = strlen(num), base_factor = 0;
		i = len - 1;

		// change base multiplication factor
		if (strcmp(base,"b") == 0)
		base_factor = 2;
		else if (strcmp(base,"o") == 0)
		base_factor = 8;
		else if (strcmp(base,"d") == 0)
		base_factor = 10;
		else
		base_factor = 16;

		/* same for binary and octal*/
		while (i >= 0)
		{
				if( num[i] <= '9')
				dec = dec  + ( num[i] - '0' ) * base_int ;
				else if ( num[i] >= 'A' && num[i] <= 'F' )
				dec = dec  + ( num[i] - 'A' + 10 ) * base_int ;
				else if (num[i] >= 'a' && num[i] <= 'f' )
				dec = dec  + ( num[i] - 'a' + 10 ) * base_int ;

				base_int = base_int * base_factor;
				i--;
		}
		return dec;

}

// check input if is correct or not
int validate_input(char *num, char *base)
{
		int i = 0;
		if (strcmp(base,"b") == 0) // there must not be a number greater than one
		{
				while (num[i] != '\0')
				{
						if( num[i] >= 50 )
						return 0;
						i++;
				}
		}
		else if (strcmp(base,"o") == 0) // no number should be greater than eight
		{
			 while (num[i] != '\0')
			 {
					if( num[i] >= 56 )
					return 0;
					i++;
			 }
		}
		else if (strcmp(base,"h") == 0) // no number should be greater than 10 and greater than F or f
		{
				while( num[i] != '\0' )
				{
						if( num[i] >= '0' && num[i] <= '9' || num[i] >= 'A' && num[i] <= 'F' || num[i] >= 'a' && num[i] <= 'f' )
						i++;
						else
						return 0;
				}
		}

		return 1;
}
