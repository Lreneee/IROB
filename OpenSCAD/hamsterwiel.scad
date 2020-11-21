rad1 = 90;
rad2 = 20;
gaten = 6;
// code
d = (rad1 + rad2)/(1+sqrt(2));
difference()
{
 cylinder(r=rad1/2, h=10, $fn=200);
 for(i=[0:gaten])
 {

translate([d/2*cos(i*360/gaten),d/2*sin(i*360/gaten),-0.5])
 cylinder(r=rad2/2,h=11);
 }
}