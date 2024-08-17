# Solve System of Linear Equations using Gaussian Elimination
by - ACRafi

This code takes in a system of linear equations in augmented matrix form and outputs its solution after transforming it into its Row Echelon and Reduced Row Echelon Form using Gaussian Elimination.
#Function Description#
turn_pos_zero() :-
This function basically implements the elemantary row operation {R1 -> R1 + c.R2}. It takes two rows(in vector of floats form) R1 & R2, value of their pivots p1 & p2 and the size of the rows(same for all rows) as arguments. As the pivot of the second row needs to turn 0, we choose our constant, c to be -p1/p2. And then plus/minus(depends on the pairity of the pivots) this constant times the corresponding element of the second row from the corresponding element of the first row and store the new transformed elements in the vector. Because there are floats involved, we set a limit for the values. We also store the position of the new pivot of the row at the end of the vector(extracted later outside the function)

turn_piv_one() :-
This function implements the {R1 -> R1.c} elementary row operation. Takes a row, r and its pivot, p(and the size of the row) as arguments. Here, we choose the constant to be reciprocal of the value of the pivot(c = 1/p) effectively turning the pivot into 1 and changing the row. 

#Code Description#

Row Ecehlon Form Transformation:
After the code takes the augmented matrix as input, it stores the positions of the pivots(first/leading non-zero element) of every row while determining the number of all-zero rows(every element of the row is 0). Then it sorts the rows putting the ones with the leftmost pivots first. Next, it finds which rows have pivots in the same position, then turning the lower row's pivot into 0 using the turn_pos_zero function If the row turns all-zero after this operation then interchanging it with the last row that is not all-zero. Else interchanging the consecuetive rows if the pivot of the current row is to the right of the pivot of the row below it. Furthermore, coducting these same checks if the pivot of the row above the current one is in the same position as the pivot of the one below it. 

Reduced Row Echelon Form Transformation:
For every row, it checks if any row above the current one has any elements in the same position of the pivot of this one and turning that element into zero if found using the turn_pos_zero function. Next, checking if the pivot of the current row is anything but 1, and in that case turning it into 1 by applying the turn_piv_one function of the row.

Finding the Solution of the System:
If the number of unknowns is greater than the number of equations or there is atleast one all-zero row then infinite solutions exist. We can allot any value we want to the extra unknowns and the corresponding unknowns of the all-zero rows One of the solutions is alloting 1 to all the extra unknowns and solving for the other unknowns.
