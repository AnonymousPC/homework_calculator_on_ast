// pages/index/index.js
const app = getApp()
const Complex = require('../../utils/complex.js')

Page({
  data: {
    expression: '',
    result: ''
  },

  onInput(e) {
    this.setData({
      expression: e.detail.value
    })
  },

  onCalculate() {
    const expr = this.data.expression.trim()
    const result = this.evaluateExpression(expr)
    this.setData({ result })
  },

  evaluateExpression(expr) {
    try {
      // 处理变量赋值
      if (expr.includes('=')) {
        const [variable, value] = expr.split('=')
        const val = this.evaluateExpression(value.trim())
        app.globalData.variables[variable.trim()] = val
        return `${variable.trim()} = ${val}`
      }

      // 替换变量
      expr = this.replaceVariables(expr)

      // 处理e和pi的估算
      expr = this.replaceConstants(expr)

      // 处理模长计算
      if (expr.startsWith('abs(') && expr.endsWith(')')) {
        const insideExpr = expr.slice(4, -1)
        const complexNumber = Complex.evaluate(insideExpr)
        if (complexNumber) {
          const modulus = complexNumber.modulus()
          return modulus.toString()
        }
      }

      // 处理复数计算
      if (expr.includes('i')) {
        const result = Complex.evaluate(expr)
        return result.toString()
      }

      // 处理普通四则运算
      const realResult = eval(expr)
      return realResult.toString()
    } catch (error) {
      return '错误的表达式'
    }
  },

  replaceVariables(expr) {
    for (let variable in app.globalData.variables) {
      const value = app.globalData.variables[variable]
      expr = expr.replace(new RegExp(`\\b${variable}\\b`, 'g'), `(${value})`)
    }
    return expr
  },

  replaceConstants(expr) {
    expr = expr.replace(/e:(\d+)/g, (match, p1) => {
      const precision = parseInt(p1)
      return Math.E.toFixed(precision)
    })
    expr = expr.replace(/pi:(\d+)/g, (match, p1) => {
      const precision = parseInt(p1)
      return Math.PI.toFixed(precision)
    })
    return expr
  }
})
