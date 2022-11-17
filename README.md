# lazybasic
A teeny, tiny BASIC interpreter

I was reading a recent article that detailed building a shell in C. The article used strtok() for lexical scanning so I thought I'd tinker a bit with the same function, having used it in simple interpreters before.

I decided to build a small BASIC.  I took a lazy approach, so I've called it Lazy BASIC.

It only has a handful of commands.  I implemented what I needed to write a BASIC program to print the entire lyrics for the song **The Twelve Days of Christmas**.  There are a couple of extra commands and 25 extra variables.

The variables are only of type int.  In fact, the only place where strings can be used is the PRINT statement.

To run the example program ( twelve.bas ) use the variant of the following command-line that's appropriate for your OS:

    lbas twelve.bas

Here's a quick synopsis of the commands:

    END
    Ends the program.

    REM
    Indicates that the line is a remark / comment.

    PRINT
    Display variables and/or string literals separated by pipe | characters. Then display a newline.
    If a semicolon ; is an argument by itself, all other arguments are skipped and no newline is displayed.

    LET a% = value
    Sets the value of a variable (such as a% ) to the value on the right of the = symbol.  The value may be a signed integer literal or a variable.

    IF value1 operator value2
    Determine whether to run the next line of code.  Valid operators are =, <>, and >.  Depending on the operator and the integer values of value1 and value2, the next     line of code may or may not execute.

    GOTO line-number
    Control is transferred to the first line with the line number matching the literal argument. A variable cannot be used as the line-number.  Lazy BASIC doesn't care     if multiple lines have the same number.

    ADD a% value
    Add a value to a variable

I'll write something more about the experience a bit later.
