kbhit() and getch() are not available for cpp libraries on macos, 

So I made an alternative header "kb_helper.h" to replicate them

You have to combine A S D W X and press Return to get keyboard input on macOS terminal