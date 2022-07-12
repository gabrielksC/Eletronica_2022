void display()
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(" |");
  lcd.setCursor(5, 1);
  lcd.print(" |");
  lcd.setCursor(5, 2);
  lcd.print(" |");
  lcd.setCursor(5, 3);
  lcd.print(" |");
  lcd.setCursor(0, 0);
  lcd.print("SPEED");
  lcd.setCursor(0, 2);
  lcd.print(VEL);
  lcd.setCursor(8, 0);
  lcd.print("RPM");
  lcd.setCursor(8, 2);
  lcd.print(RPM);

  lcd.setCursor(12, 0);
  lcd.print(" |");
  lcd.setCursor(12, 1);
  lcd.print(" |");
  lcd.setCursor(12, 2);
  lcd.print(" |");
  lcd.setCursor(12, 3);
  lcd.print(" |");

  lcd.setCursor(15, 0);
  lcd.print("TEMP");
  lcd.setCursor(15, 2);
  lcd.print(temp_amb);
  delay(1000);
}
