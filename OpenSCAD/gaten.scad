rad1 = 120; rad2 = 2; gaten = 90; 
hoek_gaten= 360/gaten; 
hoek_cos = 180 - hoek_gaten; 
hoek = hoek_cos/2; 
f = (rad1 + rad2)/(1+sqrt(2));
// code
difference()
 {
cylinder(r=rad1, h=10, $fn=200);
for(i=[0:gaten-1]) {
    d = cos(hoek)+1;
    e = rad1/d; 
    radius = rad1-e; 
    angle=i*hoek_gaten;

translate([e*cos(angle),e*sin(angle),-1]) cylinder(r=rad2,h=10);
} }
