<template>
  <div class="dashboard-container">
<!--              <p class="page_title">个人信息修改</p>-->
<!--              <el-form label-width="auto" style="max-width: 600px;margin-top: 3%;margin-left: 2%">-->
<!--                <el-form-item label="用户名">-->
<!--                  <el-input  disabled v-model="name" />-->
<!--                </el-form-item>-->
<!--                <el-form-item label="邮箱">-->
<!--                  <el-input disabled v-model="email" />-->
<!--                </el-form-item>-->
<!--                <el-form-item label="密码">-->
<!--                  <el-input type="password" v-model="" placeholder="请输入新密码" show-password/>-->
<!--                </el-form-item>-->
<!--                <el-form-item>-->
<!--                  <el-button style="margin-left: 60%" type="primary" @click="onSubmit">确认修改</el-button>-->
<!--                  <el-button @click="searchadmin">取消修改</el-button>-->
<!--                </el-form-item>-->
<!--              </el-form>-->
  </div>
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  data() {
    return {

    }
  },
  computed: {
    ...mapGetters([
      'name',
      'email',
    ])
  }
}
</script>

<style lang="scss" scoped>
.dashboard {
  .page_title{
    margin-left:15px;
    margin-top: 20px;
    font-weight: bold;

    font-size: 40px;
    color: #181818;
  }
}
</style>
