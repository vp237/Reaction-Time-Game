# Reaction Time Game

1. Introduction:

  Overall, the project we worked on was a reaction time game; as the name suggested, a player with a better “reaction time” would win the game. It had the main game and additional functionalities. The main game determined, out of two players, which one of them had responded more quickly to the red LED. The additional functionalities that we added included: 1) three rounds, 2) a random number generator to determine the LED duration, 3) false start, 4) increasing difficulty for each round. 
  
  This project required knowledge in interrupts and I/O to implement all the functionalities mentioned above. From this project, we were able to apply the concepts that we learned from previous labs (especially lab 2) to real-world situations. 

2. System Overview:

  Below is the block diagram that shows how different components interacted with each other:
  
  [![Final-Project-Diagram.jpg](https://i.postimg.cc/NfjTmyng/Final-Project-Diagram.jpg)](https://postimg.cc/5jD6Mt1G)
  
  Below is the link to the project video where we explained the design and functionalities of our game:
  
  https://youtu.be/5wUyDZ0SO8k

3. System Description:

  For this project, our design consisted of two source files, final_project.c and utils.c, and a header file, utils.h. 
  
  In utils.c, we configured the ports to initialize the buttons and the LEDs. To initialize buttons SW2 and SW3, we first enabled the clock to Ports A and C. We set PINs PTA4 and PTC6 as GPIO. We then connected SW2 and SW3 as interrupts on rising edge and assigned them as inputs. After that, we enabled the interrupts for SW2 and SW3 and set the interrupt handler for SW2 as having higher priority than SW3. To initialize the LEDs, we enabled the clock to Ports B and E. We then set PINs PTB21, PTB22, PTE26 as GPIO. After that, we switched the red, blue, and green LEDs off and enabled them as outputs. We also implemented several functions that toggled the necessary LEDs, namely LEDRed_Toggle, LEDBlue_Toggle, LEDGreen_Toggle, and LEDWhite_Toggle (white LED toggling was produced by toggling all the red, blue, and green LEDs). We also created some functions to turn on the LEDs, including LEDYellow_On (yellow was produced by turning on the red and green LEDs), LEDPurple_On (purple was produced by turning on the red and blue LEDs), and LEDCyan_On (cyan was produced by turning on the blue and green LEDs). Finally, to make the game less predictable, we implemented random number generators, which determine the amount of time an LED stays on for each round.
  
  utils.h is the header file which included all the functions implemented in utils.c.
  
  In final_project.c, we made some global variables that served different purposes: PRESSED (to indicate whether a button was pressed), FALSE_START (to indicate whether a player false-started), WHITE_PRESSED (to indicated whether a player pressed the button when the LED turned white), PLAYER1 (Player 1's score), and PLAYER2 (Player 2's score). We implemented two interrupt handlers for the two buttons SW2 (PORTC_IRQHandler) and SW3 (PORTA_IRQHandler). We only wanted to register one interrupt caused by the first button that was pressed (and disregard the other), so that the board would output the color that indicated the winner. To achieve this, we made the variable PRESSED as mentioned above. In each interrupt handler, we checked if PRESSED was 0. If it was, we toggled the LED to indicate the player that pressed the button, set PRESSED to 1, and cleared the interrupt status flag. In our main function, we implemented the game. We first called the function game_setup to initialize the LEDs and buttons. We then set the variable FALSE_START to 1 for false start detection. We then called the function easy, which started the first round of the game. In the function easy, we made a for-loop that allowed the red LED to blink twice to indicate two subrounds. At the beginning of the for loop, we set FALSE_START to 1. We only reset PRESSED and FALSE_START to 0 at the end of each subround. In the main function, after we called easy, we again set FALSE_START to 1 because the round was over. We then called medium, which was the second round of the game. For medium, the principle was similar to easy, except that we made a variable called white_red to determine which color of the LED would turn on (red or white) and used the function rand from the Standard Library. If white_red was an odd number, the red LED toggled, and we set WHITE_PRESSED to 0. If white_red was an even number, the white LED toggled and we set WHITE_PRESSED to 1. In the main function, we then reset FALSE_START to 1 and called hard, which was the third round of the game. The implementation of hard was the same as medium, except the LED stayed on for a shorter time. Finally, we called game_result, which output the color of the LED that indicated the winner of the game.

4. Testing:

  We did not test the game using the traditional test cases; instead, we interacted with the board directly. We considered all the cases that could happen during the game.
  
  If there was a false start, which happened when one of the players pressed the button when the red LED was on, a certain color of LED would flash depending on which player had done the false start. If player 1 did the false start, yellow LED would blink. If player 2 did the false start, purple LED would blink.
  
  There was also a case when one of the players pressed the button when the white LED was on. If player 1 pressed the button when the white LED was on, the purple LED would blink. For player 2, the yellow LED would blink.
    
  At the end of the game, the purple LED would blink if the player 1 won. The cyan LED would blink if the player 2 won. If there was a tie, the yellow LED would blink.
  
  Below is the chart that can be used to reference different scenarios of LED color display:
  
  [![FINAL-PROJECT.jpg](https://i.postimg.cc/HsFxnVDv/FINAL-PROJECT.jpg)](https://postimg.cc/2VFmXj5n)
  
  We tested the program every time we made modifications to the code to avoid facing complicated bugs. Because we were able to test out individual cases by loading the program into the board, we were certain that the game worked correctly. In addition, we made sure that for all of the cases considered above, the expected and the actual behavior of the board were the same.
  
5. Resources:
  
  We used the following resources to set up the LEDs and the buttons:
  
  K64 Sub-Family Reference Manual:
  https://www.mouser.com/datasheet/2/813/K64P144M120SF5RM-1074828.pdf
  
  FRDM-K64F Freedom Module User’s Guide:
  https://os.mbed.com/media/uploads/GregC/frdm-k64f_ug_rev0.1.pdf
  
  ECE 3140 - GPIO and Interrupts Slides:
  https://piazza.com/class_profile/get_resource/k5dfdqflysq1fp/k6sazbxh7r658d

6. Work Distribution:

  We executed peer programming and divided up the tasks. Abby coded the main game, while Esther made the video. We both had an opportunity to contribute to the final project. In terms of tools, we used Google Drive to share the codes, and Zoom meetings to code and collaborate on the assignment. We also met in person to record the video and work on the website together.  

