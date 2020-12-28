import processing.serial.*;

Serial myPort;
String LEDStatus = "LED Off";

void setup(){
  size(450,500);
  //println(Serial.list()[0]);
  //String portName = Serial.list()[0];
  myPort = new Serial(this, "COM5", 38400);
  myPort.bufferUntil('\n');
}

void serialEvent (Serial myPort){
  LEDStatus = myPort.readStringUntil('\n');
}

void draw(){
  background(#F8FAE3);
  fill(#6C8E5E);
  stroke(33);
  strokeWeight(1);
  rect(50, 100, 150, 50, 10);
  rect(50, 200, 150, 50, 10);
  rect(50, 300, 150, 50, 10);
  rect(50, 10, 150, 50, 10);
  
  fill(255);
  textSize(32);
  text("RED", 75, 135);
  text("BLUE", 70, 235);
  text("GREEN", 65, 335);
  text("CLEAR", 70, 45);
  fill(33);
  textSize(24);
  text("Status: ", 180, 400);
  textSize(16);
  text(LEDStatus, 180, 450);
  
  if(mousePressed && mouseX > 50 && mouseX < 200 && mouseY > 100 && mouseY < 150){
    myPort.write('0');
    
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    rect(50, 100, 150, 50, 10);
  }
  
    if(mousePressed && mouseX > 50 && mouseX < 200 && mouseY > 200 && mouseY < 250){
    myPort.write('1');
    
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    rect(50, 200, 150, 50, 10);
  }
  
    if(mousePressed && mouseX > 50 && mouseX < 200 && mouseY > 300 && mouseY < 350){
    myPort.write('2');
    
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    rect(50, 300, 150, 50, 10);
  }

    if(mousePressed && mouseX > 50 && mouseX < 200 && mouseY > 10 && mouseY < 60){
    myPort.write('3');
    
    stroke(255,0,0);
    strokeWeight(2);
    noFill();
    rect(50, 10, 150, 50, 10);
  }

}
