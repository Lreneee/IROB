height_phone = 20; 
width_phone = 20; 
rotation = -15; 

translate([width_phone/2+0.2,1, 0])
rotate([rotation, 0, 0])
cube([0.5, 2, height_phone/2-1], center=true);
translate([-width_phone/2-0.2,1, 0])
rotate([rotation, 0, 0])
cube([0.5, 2, height_phone/2-1], center=true);
translate([0, -3, 5])
rotate([rotation, 0, 0])
cube([width_phone, 18, 1], center=true);
rotate([rotation, 0, 0])
cube([width_phone, 1, height_phone], center=true);