<template>
    <div class="login-container">
      <el-form v-show="login" ref="loginForm" :model="loginForm" :rules="loginRules" class="login-form" auto-complete="on" label-position="left">

        <div class="title-container">
          <h3 class="title">Price Pulse</h3>
        </div>

        <el-form-item prop="username">
          <span class="svg-container">
            <svg-icon icon-class="user" />
          </span>
          <el-input
            ref="username"
            v-model="loginForm.username"
            placeholder="Username"
            name="username"
            type="text"
            tabindex="1"
            auto-complete="on"
          />
        </el-form-item>

        <el-form-item prop="password">
          <span class="svg-container">
            <svg-icon icon-class="password" />
          </span>
          <el-input
            :key="passwordType"
            ref="password"
            v-model="loginForm.password"
            :type="passwordType"
            placeholder="Password"
            name="password"
            tabindex="2"
            auto-complete="on"
            @keyup.enter.native="handleLogin"
          />
          <span class="show-pwd" @click="showPwd">
            <svg-icon :icon-class="passwordType === 'password' ? 'eye' : 'eye-open'" />
          </span>
        </el-form-item>

        <el-button :loading="loading" type="primary" @click.native.prevent="handleLogin">登录</el-button>

        <div class="tips">
          <span style="margin-right:20px;" @click="reset();"> 注册账号 </span>
<!--          <span> 找回密码 </span>-->
        </div>

      </el-form>

      <el-form v-show="!login" ref="registerForm" :model="registerForm" :rules="registerRules" class="register-form" auto-complete="on" label-position="left">

        <div class="title-container">
          <h3 class="title">Price Pulse</h3>
        </div>

        <el-form-item prop="username">
          <span class="svg-container">
            <svg-icon icon-class="user" />
          </span>
          <el-input
            ref="username"
            v-model="registerForm.username"
            placeholder="Username"
            name="username"
            type="text"
            tabindex="1"
            auto-complete="on"
          />
        </el-form-item>

        <el-form-item prop="email">
          <span class="svg-container">
            <svg-icon icon-class="email" />
          </span>
          <el-input
            ref="email"
            v-model="registerForm.email"
            placeholder="Email"
            name="email"
            type="email"
            tabindex="2"
            auto-complete="on"
          />
        </el-form-item>

        <el-form-item prop="password">
          <span class="svg-container">
            <svg-icon icon-class="password" />
          </span>
          <el-input
            :key="passwordType"
            ref="password"
            v-model="registerForm.password"
            :type="passwordType"
            placeholder="Password"
            name="password"
            tabindex="3"
            auto-complete="on"
            @keyup.enter.native="handleRegister"
          />
          <span class="show-pwd" @click="showPwd">
            <svg-icon :icon-class="passwordType === 'password' ? 'eye' : 'eye-open'" />
          </span>
        </el-form-item>

        <el-form-item prop="confirmPassword">
          <span class="svg-container">
            <svg-icon icon-class="password" />
          </span>
          <el-input
            ref="confirmPassword"
            v-model="registerForm.confirmPassword"
            :type="passwordType"
            placeholder="Confirm Password"
            name="confirmPassword"
            tabindex="4"
            auto-complete="on"
            @keyup.enter.native="handleRegister"
          />
        </el-form-item>

        <el-button :loading="loading" type="primary" @click.native.prevent="handleRegister">注册</el-button>

        <div class="tips">
          <span style="margin-right:20px;" @click="reset();">已有账号？登录</span>
        </div>

      </el-form>
    </div>
</template>

<script>

export default {
  data() {
    const validateUsername = (rule, value, callback) => {
      if (!value || value.length <= 6) {
        callback(new Error('用户名需大于6位'))
      }
      else if (value.length > 16) {
        callback(new Error('用户名不可超过16位'))
      }
      else {
        callback()
      }
    }
    const validatePassword = (rule, value, callback) => {
      if (!value || value.length <= 6) {
        callback(new Error('密码需大于6位'))
      }
      else if (value.length > 16) {
        callback(new Error('密码不可超过16位'))
      }
      else {
        callback()
      }
    }
    const validateConPassword = (rule, value, callback) => {
      if (value && value !== this.$refs.password.value) {
        callback(new Error('两次密码不一致'))
      } else {
        callback()
      }
    }
    const validateEmail = (rule, value, callback) => {
      if (!value) {
        callback(new Error('请填写邮箱'))
      } else {
        callback()
      }
    }

    return {
      loginForm: {
        username: '',
        password: ''
      },
      loginRules: {
        username: [{ required: true, trigger: 'blur', validator: validateUsername }],
        password: [{ required: true, trigger: 'blur', validator: validatePassword }]
      },
      registerForm: {
        username: '',
        password: '',
        confirmPassword: '',
        email: ''
      },
      registerRules: {
        username: [{ required: true, trigger: 'blur', validator: validateUsername }],
        password: [{ required: true, trigger: 'blur', validator: validatePassword }],
        confirmPassword: [{ required: true, trigger: 'blur', validator: validateConPassword }],
        email: [{ required: true, trigger: 'blur', validator: validateEmail }]
      },
      loading: false,
      passwordType: 'password',
      redirect: undefined,
      login: true,
    }
  },
  watch: {
    $route: {
      handler: function(route) {
        this.redirect = route.query && route.query.redirect
      },
      immediate: true
    }
  },
  methods: {
    showPwd() {
      if (this.passwordType === 'password') {
        this.passwordType = ''
      } else {
        this.passwordType = 'password'
      }
      this.$nextTick(() => {
        this.$refs.password.focus()
      })
    },

    reset() {
      this.passwordType = 'password'
      this.loginForm = {}
      this.registerForm = {}
      this.$refs.loginForm.resetFields()
      this.$refs.registerForm.resetFields()
      this.login = !this.login
    },

    handleRegister() {
      this.$refs.registerForm.validate(valid => {
       if (valid) {
         this.loading = true
         this.$store.dispatch('user/register', this.registerForm).then(response => {
           if (response.includes('成功')) {
             this.$message.success(response)
             this.reset()
           }
           else
             this.$message.error(response)
           this.loading = false
         }).catch(error => {
           console.log(error)
           this.loading = false
         })
       } else {
         this.$message.error('请检查所填信息格式')
       }
    })
    },

    handleLogin() {
      this.$refs.loginForm.validate(valid => {
        if (valid) {
          this.loading = true
          this.$store.dispatch('user/login', this.loginForm).then(response => {
            this.$router.push({path: this.redirect || '/dashboard/index'})
            if (response.includes('成功'))
              this.$message.success(response)
            else
              this.$message.error(response)
            this.loading = false
          }).catch(error => {
            console.log(error)
            this.loading = false
          })
        }
        else {
          this.$message.error('请检查所填信息格式')
        }
      })
    }
  }
}
</script>

<style lang="scss">
/* 修复input 背景不协调 和光标变色 */


$bg:#283443;
$light_gray:#fff;
$cursor: #fff;

@supports (-webkit-mask: none) and (not (cater-color: $cursor)) {
   .login-container .el-input input {
    color: #494949;
  }
}

/* reset element-ui css */
.login-container {
  .el-input {
    display: inline-block;
    height: 47px;
    width: 85%;

    input {
      background: transparent;
      border: 0px;
      -webkit-appearance: none;
      border-radius: 0px;
      padding: 12px 5px 12px 15px;
      color: #494949;
      height: 47px;
      caret-color: #494949;

      &:-webkit-autofill {
      -webkit-text-fill-color: #494949 !important;
      transition: background-color 5000s ease-in-out 0s !important;
      }

    }
  }

  .el-form-item {
    border: 1px solid rgba(255, 255, 255, 0.1);
    background: rgba(0, 0, 0, 0.1);
    border-radius: 5px;
    color: #454545;
  }

  .el-button {
    width:100%;
    margin-bottom:30px;
    font-weight:bold;
    background-color: #494949;
    border-color: #494949;
    transition: background-color 0.3s;

    &:hover {
      background-color: gray;
      border-color: gray;
    }
  }
}

</style>

<style lang="scss" scoped>
$bg:#2d3a4b;
$dark_gray:#889aa4;
$light_gray:#eee;

.login-container {
  background-image: url(bg.png);
  background-position: center center;
	background-repeat: no-repeat;
	background-attachment: fixed;
	background-size: cover;
  min-height: 100%;
  width: 100%;
  overflow: hidden;
  top: 50px;
  font-family: 'PingFang SC',sans-serif;
  font-weight: bold;
  color: #494949;

  .login-form {
    position: relative;
    width: 420px;
    max-width: 100%;
    padding: 160px 35px 0;
    margin: 80px auto;
    overflow: hidden;
    box-shadow: 0 80px 30px 10px rgba(0, 0, 0, 0.2);
    transition: transform 0.3s ease-in-out, box-shadow 0.3s ease-in-out;
    border-width: 2px;
    border-radius: 30px;
    border-style: dashed;
  }


  .register-form {
    position: relative;
    width: 420px;
    max-width: 100%;
    padding: 160px 35px 0;
    margin: 20px auto;
    overflow: hidden;
    box-shadow: 0 30px 30px 8px rgba(0, 0, 0, 0.2);
    transition: transform 0.3s ease-in-out, box-shadow 0.3s ease-in-out;
    border-width: 2px;
    border-radius: 30px;
    border-style: dashed;
  }

  .tips {
    font-size: 14px;
    //color: #fff;
    margin-bottom: 30px;

    span {
      cursor: pointer;
      font-weight: bold;
      //color: $dark_gray;
      transition: color 0.3s;

      &:hover {
        color: gray;
      }

      &:first-of-type {
        margin-right: 16px;
      }
      }
  }

  .svg-container {
    padding: 6px 5px 6px 15px;
    //color: $dark_gray;
    vertical-align: middle;
    width: 30px;
    display: inline-block;
  }

  .title-container {
    position: relative;
    margin-top: -60px;

    .title {
      font-style: italic;
      font-size: 60px;
      font-family: 'Georgia', sans-serif;
      margin: 0 auto 80px auto;
      text-align: center;
    }
  }

  .show-pwd {
    position: absolute;
    right: 10px;
    top: 7px;
    font-size: 16px;
    //color: $dark_gray;
    cursor: pointer;
    user-select: none;
  }

  @media screen and (max-width: 768px) {
    background-position: center center;
    top: 0;
    display: flex;
    align-items: center;
    min-height: 100vh;

    .login-form,
    .register-form {
      width: 90%;
      margin: 0 auto;
      padding: 80px 20px 40px;
      box-shadow: 0 40px 20px 5px rgba(0, 0, 0, 0.2);
      transform: translateY(-10%);

      .title-container {
        margin-top: -40px;

        .title {
          font-size: 40px;
          margin: 0 auto 40px auto;
        }
      }

      .el-input {
        width: 85%;

        input {
          padding: 12px 5px 12px 15px;
        }
      }

      .el-button {
        height: 44px;
        margin-bottom: 20px;
      }

      .tips {
        font-size: 13px;
        margin-bottom: 20px;
      }
    }

    .svg-container {
      padding: 6px 5px 6px 12px;
    }
  }
}

</style>
