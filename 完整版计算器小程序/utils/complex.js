// utils/complex.js
class Complex {
  constructor(a, b) {
    this.a = a; // 实部
    this.b = b; // 虚部
  }

  static fromString(str) {
    // 移除空格
    str = str.replace(/\s+/g, '');

    // 特殊处理 'i'、'+i'、'-i'
    if (str === 'i' || str === '+i') return new Complex(0, 1);
    if (str === '-i') return new Complex(0, -1);

    // 匹配形如 'a+bi'、'a-bi'、'bi'、'a' 等形式
    const regex = /^([+-]?[\d\.]+)?([+-]?[\d\.]*)i?$/;
    const match = str.match(regex);

    if (match) {
      let a = 0;
      let b = 0;

      if (match[2]) {
        // 存在虚部
        if (match[2] === '+' || match[2] === '-') {
          b = parseFloat(match[2] + '1');
        } else {
          b = parseFloat(match[2]);
        }
      }

      if (match[1]) {
        a = parseFloat(match[1]);
      }

      return new Complex(a, b);
    } else {
      throw new Error('无法解析复数: ' + str);
    }
  }

  toString() {
    let result = '';
    if (this.a !== 0) result += this.a;
    if (this.b > 0) result += (this.a !== 0 ? '+' : '') + this.b + 'i';
    else if (this.b < 0) result += this.b + 'i';
    else if (this.a === 0) result = '0';
    return result;
  }

  add(other) {
    return new Complex(this.a + other.a, this.b + other.b);
  }

  subtract(other) {
    return new Complex(this.a - other.a, this.b - other.b);
  }

  multiply(other) {
    const a = this.a * other.a - this.b * other.b;
    const b = this.a * other.b + this.b * other.a;
    return new Complex(a, b);
  }

  divide(other) {
    const denominator = other.a ** 2 + other.b ** 2;
    const a = (this.a * other.a + this.b * other.b) / denominator;
    const b = (this.b * other.a - this.a * other.b) / denominator;
    return new Complex(a, b);
  }

  modulus() {
    return Math.sqrt(this.a ** 2 + this.b ** 2);
  }

  static evaluate(expr) {
    // 移除空格
    expr = expr.replace(/\s+/g, '');

    // 将中缀表达式转换为后缀表达式
    const postfix = Complex.infixToPostfix(expr);
    const stack = [];

    postfix.forEach(token => {
      if (Complex.isOperator(token)) {
        const b = stack.pop();
        const a = stack.pop();
        if (!a || !b) {
          throw new Error('表达式错误');
        }
        let result;
        switch (token) {
          case '+':
            result = a.add(b);
            break;
          case '-':
            result = a.subtract(b);
            break;
          case '*':
            result = a.multiply(b);
            break;
          case '/':
            result = a.divide(b);
            break;
        }
        stack.push(result);
      } else {
        // 解析数字或复数
        const complexNumber = Complex.fromString(token);
        stack.push(complexNumber);
      }
    });

    if (stack.length !== 1) {
      throw new Error('表达式错误');
    }

    return stack.pop();
  }

  static infixToPostfix(expr) {
    const output = [];
    const operators = [];

    // 令牌化表达式
    const tokens = Complex.tokenize(expr);

    const precedence = {
      '+': 1,
      '-': 1,
      '*': 2,
      '/': 2
    };

    tokens.forEach(token => {
      if (Complex.isOperator(token)) {
        while (
          operators.length &&
          operators[operators.length - 1] !== '(' &&
          precedence[operators[operators.length - 1]] >= precedence[token]
        ) {
          output.push(operators.pop());
        }
        operators.push(token);
      } else if (token === '(') {
        operators.push(token);
      } else if (token === ')') {
        while (operators.length && operators[operators.length - 1] !== '(') {
          output.push(operators.pop());
        }
        operators.pop(); // 弹出 '('
      } else {
        output.push(token);
      }
    });

    while (operators.length) {
      output.push(operators.pop());
    }

    return output;
  }

  static tokenize(expr) {
    const tokens = [];
    let number = '';
    let i = 0;

    while (i < expr.length) {
      const char = expr[i];

      if (char.match(/[0-9.]/)) {
        // 数字的一部分
        number += char;
        i++;
      } else if (char === 'i') {
        // 虚数单位
        if (number === '' || number === '+' || number === '-') {
          number += '1';
        }
        tokens.push(number + 'i');
        number = '';
        i++;
      } else if (char.match(/[+\-*/()]/)) {
        if (number !== '') {
          tokens.push(number);
          number = '';
        }
        // 处理一元加减
        if ((char === '+' || char === '-') && (i === 0 || expr[i - 1] === '(' || Complex.isOperator(expr[i - 1]))) {
          number += char;
          i++;
        } else {
          tokens.push(char);
          i++;
        }
      } else {
        // 无效字符
        throw new Error('表达式中包含无效字符: ' + char);
      }
    }

    if (number !== '') {
      tokens.push(number);
    }

    return tokens;
  }

  static isOperator(token) {
    return ['+', '-', '*', '/'].includes(token);
  }
}

module.exports = Complex;
