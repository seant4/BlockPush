#pragma once


/*
 * Creates a black fade in or fade out effect
 * @param
 * 	int timer - What to count up or down to.
 * 		Ex: If fading in (opaque to transparent) set > 0
 * 			If fading out (transparent to opaque) set = 0
 * 	int amount - Multiplyer for speed
 * 	int fade - Which direction to go (fade in or out)
 * 		Ex: If fading in (opaque to transparent) set = 0
 * 			If fading out (transparen to opaque) set = 1
 */
struct Fade{
	int timer;
	int amount;
	int fade; 
};

/* Modifies timer to set new opacity
 *
 * @param: a Fade* struct
 * @return: boolean if finished fading
 */
bool updateFade(Fade* fader);

/* Draws the fading black rectangle to the screen
 *
 * @param: a Fade* struct
 */
void drawFade(Fade* fader);

