<template>
  <div class="info-container">
    <el-tabs v-model="activeTab" type="border-card">
      <!-- 个人信息标签页 -->
      <el-tab-pane label="个人信息" name="profile">
        <el-form
          ref="profileForm"
          :model="profileForm"
          :rules="rules"
          label-width="100px"
          class="profile-form"
        >
          <el-form-item label="用户名" prop="name">
            <el-input v-model="profileForm.name" placeholder="请输入用户名"></el-input>
          </el-form-item>

          <el-form-item label="邮箱" prop="email">
            <el-input v-model="profileForm.email" placeholder="请输入邮箱（用于接收降价提醒）"></el-input>
          </el-form-item>

          <el-form-item>
            <el-button type="primary" @click="updateProfile">保存修改</el-button>
          </el-form-item>
        </el-form>
      </el-tab-pane>

      <!-- 降价提醒标签页 -->
      <el-tab-pane label="降价提醒" name="priceAlerts">
        <span slot="label">
          降价提醒
          <el-badge v-if="unreadAlertsCount > 0" :value="unreadAlertsCount" class="alert-badge"/>
        </span>
        <div v-if="priceAlerts.length === 0" class="empty-alerts">
          <el-empty description="暂无降价提醒"></el-empty>
        </div>

        <el-card
          v-for="alert in priceAlerts"
          :key="alert.id"
          class="alert-card"
          shadow="hover"
        >
          <div class="alert-content">
            <div class="product-info">
              <img :src="alert.img" :alt="alert.title" class="product-image">
              <div class="product-details">
                <h3 class="product-title">{{ alert.title }}</h3>
                <div class="price-change">
                  <div class="old-price">
                    原价：<span>¥{{ alert.old_price }}</span>
                  </div>
                  <div class="new-price">
                    现价：<span>¥{{ alert.new_price }}</span>
                  </div>
                  <div class="price-diff">
                    降价：<span class="decrease">-¥{{ (alert.old_price - alert.new_price).toFixed(2) }}</span>
                  </div>
                </div>
                <div class="alert-time">
                  降价时间：{{ formatTime(alert.time) }}
                </div>
              </div>
            </div>
            <div class="alert-actions">
              <a :href="alert.link"
                 target="_blank"
                 class="el-button el-button--primary el-button--small"
              >
                查看商品
              </a>
              <el-button
                type="danger"
                size="small"
                @click="dismissAlert(alert.id)"
              >
                忽略提醒
              </el-button>
            </div>
          </div>
        </el-card>
      </el-tab-pane>
    </el-tabs>
  </div>
</template>

<script>
import { mapGetters } from 'vuex'
import axios from 'axios'

export default {
  name: 'Info',

  data() {
    return {
      activeTab: 'profile',
      profileForm: {
        name: '',
        email: ''
      },
      rules: {
        name: [
          { required: true, message: '请输入用户名', trigger: 'blur' },
          { min: 7, max: 32, message: '长度在 7 到 32 个字符', trigger: 'blur' }
        ],
        email: [
          { required: true, message: '请输入邮箱地址', trigger: 'blur' },
          { type: 'email', message: '请输入正确的邮箱地址', trigger: 'blur' }
        ]
      },
      priceAlerts: [],
      alerts: [],
      unreadAlertsCount: 0,
      alertsTimer: null
    }
  },

  computed: {
    ...mapGetters([
      'id',
      'name',
      'email'
    ])
  },

  created() {
    // 初始化表单数据
    this.profileForm.name = this.name
    this.profileForm.email = this.email

    // 获取降价提醒
    this.fetchPriceAlerts()

    // 定期更新提醒
    this.alertsTimer = setInterval(() => {
      this.getAlerts()
    }, 30000) // 每30秒更新一次
  },

  beforeDestroy() {
    // 清除定时器
    if (this.alertsTimer) {
      clearInterval(this.alertsTimer)
    }
  },

  methods: {
    // 更新个人信息
    updateProfile() {
      this.$refs.profileForm.validate(valid => {
        if (valid) {
          axios.post('/compare/info/', {
            method: 'update_profile',
            user_id: this.$store.getters.id,
            name: this.profileForm.name,
            email: this.profileForm.email
          }).then(response => {
            if (response.data.message === 'success') {
              this.$message.success('个人信息更新成功')
              // 更新 Vuex store 中的用户信息
              this.$store.dispatch('user/updateUserInfo', {
                name: this.profileForm.name,
                email: this.profileForm.email
              })
            } else {
              this.$message.error('更新失败：' + response.data.message)
            }
          }).catch(error => {
            console.error('更新失败:', error)
            this.$message.error('更新失败，请重试')
          })
        }
        else
          this.$message.error('请检查所填信息格式')
      })
    },

    // 获取降价提醒
    fetchPriceAlerts() {
      axios.get('/compare/info/', {
        params: {
          method: 'get_alerts',
          user_id: this.id
        }
      }).then(response => {
        if (response.data.message === 'success') {
          this.priceAlerts = response.data.alerts
          // 计算未读提醒数量
          this.unreadAlertsCount = this.priceAlerts.filter(alert => !alert.is_read).length
        } else {
          this.$message.error('获取降价提醒失败')
        }
      }).catch(error => {
        console.error('获取降价提醒失败:', error)
        this.$message.error('获取降价提醒失败，请重试')
      })
    },

    // 忽略降价提醒
    dismissAlert(alertId) {
      axios.post('/compare/info/', {
        method: 'dismiss_alert',
        user_id: this.id,
        alert_id: alertId
      }).then(response => {
        if (response.data.message === 'success') {
          this.$message.success('已忽略该提醒')
          // 从列表中移除该提醒
          this.priceAlerts = this.priceAlerts.filter(alert => alert.id !== alertId)
          // 更新未读提醒数量
          this.unreadAlertsCount = this.priceAlerts.length
        } else {
          this.$message.error('操作失败')
        }
      }).catch(error => {
        console.error('操作失败:', error)
        this.$message.error('操作失败，请重试')
      })
    },

    // 格式化时间
    formatTime(timeStr) {
      // 直接处理后端返回的时间字符串
      if (timeStr) {
        // 如果包含 'T'，替换为空格
        return timeStr.replace('T', ' ').substring(0, 16)
      }
      return ''
    },

    getAlerts() {
      this.$axios.get('/compare/info/', {
        params: {
          method: 'get_alerts',
          user_id: this.$store.getters.id
        }
      }).then(response => {
        if (response.data.message === 'success') {
          this.alerts = response.data.alerts
          // 计算未读提醒数量
          this.unreadAlertsCount = this.alerts.filter(alert => !alert.is_read).length
        }
      }).catch(error => {
        console.error('获取降价提醒失败:', error)
      })
    }
  }
}
</script>

<style lang="scss" scoped>
.info-container {
  padding: 20px;

  .profile-form {
    max-width: 500px;
    margin: 20px auto;
  }

  .alert-card {
    margin-bottom: 20px;
    border-radius: 8px;

    .alert-content {
      .product-info {
        display: flex;
        gap: 20px;

        .product-image {
          width: 120px;
          height: 120px;
          object-fit: cover;
          border-radius: 4px;
        }

        .product-details {
          flex: 1;

          .product-title {
            margin: 0 0 12px;
            font-size: 16px;
            line-height: 1.4;
            color: #303133;
          }

          .price-change {
            margin-bottom: 12px;
            font-size: 14px;

            .old-price {
              color: #909399;
              text-decoration: line-through;
            }

            .new-price {
              color: #303133;
              font-weight: bold;
              margin: 4px 0;
            }

            .price-diff {
              .decrease {
                color: #67c23a;
                font-weight: bold;
              }
            }
          }

          .alert-time {
            font-size: 12px;
            color: #909399;
          }
        }
      }

      .alert-actions {
        margin-top: 16px;
        display: flex;
        justify-content: flex-end;
        gap: 12px;
      }
    }
  }

  .empty-alerts {
    padding: 40px 0;
  }

  .alert-badge {
    position: absolute;
    top: 2px;
    right: 11px;
    transform: translateX(50%);

    ::v-deep .el-badge__content {
      background-color: #f56c6c;
      border: none;
      height: 16px;
      min-width: 16px;
      padding: 0 4px;
      line-height: 16px;
      font-size: 12px;
      border-radius: 8px;
      box-shadow: 0 0 0 1px #fff;
    }

    // 当数字小于10时使用更小的圆形徽标
    ::v-deep .el-badge__content:not(.is-fixed) {
      &:not(.el-badge__content--large) {
        transform: scale(0.8);
        transform-origin: right top;
      }
    }
  }
}

// 响应式布局
@media screen and (max-width: 768px) {
  .info-container {
    padding: 10px;

    .alert-card {
      .alert-content {
        .product-info {
          flex-direction: column;

          .product-image {
            width: 100%;
            height: 200px;
          }
        }
      }
    }
  }
}

.alert-actions {
  a.el-button {
    display: inline-flex;
    align-items: center;
    justify-content: center;
    text-decoration: none;
    line-height: 1;
    white-space: nowrap;
    cursor: pointer;
  }
}
</style>
