int get() {
  if (stack.isEmpty()) {
    return 0;
  }
  return stack.pop();
}

void push(int n) {
  stack.push(n);
}

int get2() {
  if (stack2.isEmpty()) {
    return 0;
  }
  return stack2.pop();
}

void push2(int n) {
  stack2.push(n);
}

void log(String s) {
  Serial.println(s);
}

void log(int s) {
  Serial.println(s);
}

int* reg(String s) {
  if (s[1] == "X") {
    if (s[0] == "A") {
      return &ax;
    }
  }
}

void kill() {
  log("STARTED_CONSOLE_MOD");
  log("");
  while (1) {
    if (Serial.available()) {
      buffer = Serial.readStringUntil("\n");
      execute(buffer);
    }
  }
}
