# Assignment 7 - Supply delivery optimization

You are given a road network of the state of Tamilnadu, where there are 3 kinds
of roads: primary, secondary, and tertiary.
The data format is as follows:

* Line 1: Number of points or nodes (N)
* Line 2 to N+1: Longitude and Latitude values of points (type float).
* Line N+2: Number of road edges (R)
* Line N+3 to end of file (N+3+R-1): one road segment per line

The format of a road segment is as follows:

* src: ID of the source node (0 to N-1)
* dst: ID of destination node
* type: p for primary, s for secondary, t for tertiary
* distance: distance along segment in km

Supplies can be transported from one point to another using supply trucks.  
Primary roads can carry up to 100 trucks per hour, but have a maximum speed
constraint of 60kph. Secondary roads can carry up to 50 trucks per hour at a
maximum of 40kph, while tertiary roads can carry 20 trucks per hour at 30kph.  
The number of trucks per hour on a road must be an integer.

Refer the PDF for the questions.