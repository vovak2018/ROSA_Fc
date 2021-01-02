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
