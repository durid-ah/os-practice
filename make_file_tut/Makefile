
# all target used to run all the targets
all: clean blah some_file

######################################################

# this shows files depending on each other
blah: blah.o
	cc blah.o -o blah # runs third

blah.o: blah.c
	cc -c blah.c blah.o # runs second

blah.c:
	echo "int main() { return 0; }" > blah.c # runs first

######################################################


# `x` is a string variable
x := he he hey

some_file:
	echo "This line will always print"
	echo ${x}

#######################################################

# * wildcard:
thing := $(wildcard blah*) # displays all files that start with blah
first_wild_card:
	echo ${thing}

#######################################################

# automatic variables
hey: one two
	# Outputs "hey", since this is the first target
	echo $@

	# Outputs all prerequisites newer than the target
	echo $?

	# Outputs all prerequisites
	echo $^

	touch hey

one:
	touch one

two:
	touch two


blah_files := $(wildcard blah*)
clean:
	rm ${blah_files} hey one two