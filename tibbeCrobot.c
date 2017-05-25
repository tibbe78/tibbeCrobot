
/* tibbe */
/* strategy: move like hell and avoid everyone, shooot */
/* Assume everything is in meters */


/* The battlefield of the walls normal 0-1000 meters - asume its a square in meters 
	The battlefield is a 1,000 by 1,000 meter square.  
	The lower left corner has the coordinates x = 0, y = 0; the upper
	right corner has the coordinated x = 999, y = 999.
	A wall
	surrounds the perimeter, so that a robot running into the wall
	will incur damage.
	
	The scanner is an optical device that can instantly scan any
	chosen heading, 0-359.  The scanner has a maximum resolution of  
	+/- 10 degrees.  This enables the robot to quickly scan the field
	at a low resolution, then use maximum resolution to pinpoint an
	opponent.
	
	The scan() function invokes the robot's scanner, at a specified
	degree and resolution.  scan() returns 0 if no robots are
	within the scan range or a positive integer representing the
	range to the closest robot.  Degree should be within the range
	0-359, otherwise degree is forced into 0-359 by a modulo 360
	operation, and made positive if necessary.  Resolution controls
	the scanner's sensing resolution, up to +/- 10 degrees.
	Examples:
	range = scan(45,0);  scan 45, with no variance 
	range = scan(365,10);  scans the range from 355 to 15 
	
	
	The direction of the cannon and tank in 0-360 degrees 
	The compass system is oriented so that due east (right) is 0
	degrees, 90 is north, 180 is west, 270 is south.  One degree
	below due east is 359.
	
	Q2 135   90  45 Q1
	\   |  / 
	\  | /
	180 --- x --- 0
	/   |   \
	/    |    \ 
	Q3 225   270   315 Q4
*/


int 
tnkDir, 	/* the direction of the tank in 0-360 degrees */
cOpAng, 	/* Current Angle of opponent */
scnDist, 	/* Scan distance returned from scan 0 if not found max 700 for cannon reach */
tnkWall, 	/* Are we inside wall zone? */
tnkTurn,	/* have the tank turned? */
inZone,		/* Is the tank in the wall zone */
fireOk,		/* if it's ok to fire */
pOpAng,		/* Prevoius angle of opponent */
pScnDist; 	/* prevoius Scan distance returned from scan 0 if not found max 700 for cannon reach */


/*int tnkFlag;	 what does the tank think about in a binary 8 bit, 
	0 0 0 0 0 0 0 value
	7 6 5 4 3 2 1 bit number
	bit 1 = Turn the tank
	bit 2 = Turning
*/

/*--------------------------------------------------------------------------------------------*/

/*
	
	TEMP CODE PASTE PLACE!!
	
*/


/*  main loop */
main()
{
	
	/*--------------------------------------------------------------------------------------------*/
	/* Init values not needed right now as we do most static to minimize  */ 
	/*
		max missile Range = 700;
		max field size = 999;
		min field size = 0;
		
		Bound box for tank max = 900;
		Bound box for tank min = 100;
		
		aritmic scale for atan =  100000; 
		tank max power (speed) = 100;
		tank Thought (future relase) = 0;
	*/
	fireOk = 1;
	
	/* scnStat = 0;  First value 0 for not found and init */
	if (loc_y() > loc_x()) drive((tnkDir = rand(80) + 5 - (loc_x()/11) - (loc_y()/11)),100);
	else drive((tnkDir = rand(80) + 5 + (loc_x()/11) + (loc_y()/11)),100);
	cOpAng = tnkDir; /* set current opponent angle first time */
	DoScnLo(1); /* do a low scan to find him again with first scan enable */
	DoScnMd(1); /* do a medium scan with first scan enable */
	pOpAng = cOpAng; pScnDist = scnDist; /* uppdatera föregående värden */
	
	/* End of one time program and start of loop */
	/*--------------------------------------------------------------------------------------------*/
	
	
	while(1) {  
		/* ----------------------- MAIN Logic for Wall Avoidance -------------------------- */
		
		if (fireOk) { /* if it's ok to fire again. */
			
			/* ----------------------- MAIN Logic for Fireing -------------------------- */
			if (DoScnHi()) { /* do a high scan to get a fire solution */
				if (scnDist < 710) { 
					cannon(cOpAng-((pOpAng-cOpAng) % 360),scnDist-(pScnDist-scnDist));
				}
			} /* ----------------------- MAIN Logic for finding opponent again -------------------------- */
			else if (DoScnMd(0)) { /* do a medium scan with first scan disable */
			}
			else if (DoScnLo(0) && !tnkWall) { /* do a low scan to find him again with first scan disable  */
				if (DoScnMd(1) && !tnkWall) { /* do a medium scan with first scan enable */
				}
			}
			else if (DoScnLo(1) && !tnkWall) { /* do a low scan to find him again with first scan enable */
				if (DoScnMd(1) && !tnkWall) { /* do a medium scan with first scan enable */
				} 
			}
		} /* End of Fire ok scenario */
		
		if (tnkWall) { /* have we hit a wall and should start turning */
			if (tnkTurn) {  /* should we start turning (only once) */
				if (loc_y() > loc_x()) (tnkDir = rand(80) + 5 - (loc_x()/11) - (loc_y()/11)); /* calc a new turn based on the x & y position of the tank., 11 is to get about 90 degree from position  */
				else (tnkDir = rand(80) + 5 + (loc_x()/11) + (loc_y()/11)); /* calc a new turn based on the x & y position of the tank. flip if y<x., 11 is to get about 90 degree from position */
				tnkTurn = 0; /* stop turning */
			}
			if (speed() < 50) { 
				drive(tnkDir,100); /* if the speed is below 50, full speed ahead in new direction*/
				tnkWall = 0;
				fireOk = 1;
			}
		} /* wall scenario */
		else {	
			pOpAng = cOpAng; pScnDist = scnDist; /* uppdatera föregående värden */
			
			if (loc_x() > 850 || loc_x() < 150 || loc_y() > 850 || loc_y() < 150) { /* check if we get into the wall zone again */
				if (!inZone) {
					tnkWall = 1; tnkTurn = 1; fireOk = 0; inZone = 1; /* start the wall scenario and turn */
					drive(tnkDir,0); /* stop the engine */
				}
			}
			else {
				inZone = 0; 
			}
			
		}
	} /* End of while() */
} /* End of main() */

/*--------------------------------------------------------------------------------------------*/
/* End of program and start of functions */


/*--------------------------------------------------------------------------------------------*/
/* DoScnLo around with max 20 degree jumps starting from startDir up to 170 degree, 10 degree resolution */
DoScnLo(frstScn) {	
	
	if (frstScn) {
		if (( scnDist = scan(cOpAng, 10))) { /* 10 degree resolution scan 10 + | + 10 */
			return 1;
		}
		if (( scnDist = scan(cOpAng + 10, 10))) { 
		cOpAng += 10;
		return 1;
		}
		if (( scnDist = scan(cOpAng - 10, 10))) {
			cOpAng -= 10;
			return 1;
		}	
	}
	if (( scnDist = scan(cOpAng + 30, 10))) { 
		cOpAng += 30;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 30, 10))) {
		cOpAng -= 30;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 50, 10))) { 
		cOpAng += 50;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 50, 10))) {
		cOpAng -= 50;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 70, 10))) { 
		cOpAng += 70;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 70, 10))) {
		cOpAng -= 70;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 90, 10))) { 
		cOpAng += 90;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 90, 10))) {
		cOpAng -= 90;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 110, 10))) { 
		cOpAng += 110;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 110, 10))) {
		cOpAng -= 110;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 130, 10))) { 
		cOpAng += 130;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 130, 10))) {
		cOpAng -= 130;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 150, 10))) { 
		cOpAng += 150;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 150, 10))) {
		cOpAng -= 150;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 170, 10))) { 
		cOpAng += 170;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 170, 10))) {
		cOpAng -= 170;
		return 1;
	}	
	return 0;
}

/*--------------------------------------------------------------------------------------------*/
/* DoScnMe around with max 8 degree jumps starting from startDir up to 32 degree, 4 degree resolution */
DoScnMd(frstScn) {	
	if (frstScn) {
		if (( scnDist = scan(cOpAng, 4))) { /* 4 degree resolution scan 4 + | + 4 */
			return 1;
		}
		if (( scnDist = scan(cOpAng + 8, 4))) { 
			cOpAng += 8;
			return 1;
		}
		if (( scnDist = scan(cOpAng - 8, 4))) {
			cOpAng -= 8;
			return 1;
		}	
	}
	if (( scnDist = scan(cOpAng + 16, 4))) { 
		cOpAng += 16;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 16, 4))) {
		cOpAng -= 16;
		return 1;
	}		
	if (( scnDist = scan(cOpAng + 24, 4))) { 
		cOpAng += 24;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 24, 4))) {
		cOpAng -= 24;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 32, 4))) { 
		cOpAng += 32;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 32, 4))) {
		cOpAng -= 32;
		return 1;
	}	
	
	return 0;
}

/*--------------------------------------------------------------------------------------------*/
/* DoScnHi around with min 4 degree jumps starting from startDir up to 12 degree, 2 degree resolution */
DoScnHi() {	
	if (( scnDist = scan(cOpAng, 2))) { /* 2 degree resolution scan 2 + | + 2 */
		return 1;
	}
	if (( scnDist = scan(cOpAng + 4, 2))) { 
		cOpAng += 4;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 4, 2))) {
		cOpAng -= 4;
		return 1;
	}	
	if (( scnDist = scan(cOpAng + 8, 2))) { 
		cOpAng += 8;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 8, 2))) {
		cOpAng -= 8;
		return 1;
	}		
	if (( scnDist = scan(cOpAng + 12, 2))) { 
		cOpAng += 12;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 12, 2))) {
		cOpAng -= 12;
		return 1;
	}		
	if (( scnDist = scan(cOpAng + 16, 2))) { 
		cOpAng += 16;
		return 1;
	}
	if (( scnDist = scan(cOpAng - 16, 2))) {
		cOpAng -= 16;
		return 1;
	}	
	return 0;
}
