iprat
=====

Information Privacy Risk Assessment Tool

build
====

Run: make

run
====

./validator [-cvh] [STATE]

	-c		Create all possible states and print them to stdout.
			Each of these states can be used for input to the validator. Use './validator -c > results'.
	-C		Create all states and validate them. Prints results to stdout.
	-v [STATE]	Validate a single state, result is printed to stdout. 
	-h		Print help.
	

	The state consists of 9 assessable values (with value 1-6) in following order (the three letter abbreviations are shown in parentheses):
			1: Attack actualization (ATT)
			2: Privacy damage (PRD)
			3: Data capabilities (DAC)
			4: Asset access (ASA)
			5: Asset role (ASR)
			6: Data access (DAA)
			7: Data quantity (DAQ)
			8: Data significance (DAS)
			9: Data storage time (DST)
			10: Data identifiability (DIF) - value 1-3

	An example state: 112233445
