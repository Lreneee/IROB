spijlen = 10; 
rad1 =80; 
rad2 = 70; 

module hamsterwiel() {
    
    $fn=50;
    color("white")
    minkowski(){
        translate([0, -rad1, 15])
    	cube([100, 5, 10], center=true);
        cylinder(r=5, h=30, center=true);
        }
	difference() {
		union() {
            translate([0, 0, 15])
			difference () {
                color("lightblue")
				cylinder(h=55, r=rad1, center=true, $fn=200) ;
                 color("lightblue")
				cylinder(h=60, r=rad2, center=true, $fn=96) ;
			}
			rotate([0, 90, 0]) {
				for (r = [0:spijlen]) {
                     color("lightblue")
					rotate ([360 * r/spijlen, 0, 0]) { cylinder(h=rad1, r=3, $fn=16) ; }
				}
			}
             color("lightblue")
			cylinder(h=10, r=5, center=true, $fn=100) ;
		}
         color("lightblue")
		cylinder(h=35, r=4, center=true, $fn=100) ;
	}
}

hamsterwiel() ;