<template>
  <div class="like-container">
    <el-card class="like-header">
      <div slot="header" class="header-content">
        <span class="title">我喜欢的</span>
        <span class="subtitle">共{{ likedProducts.length }}件商品</span>
      </div>
    </el-card>

    <div class="products-grid">
      <el-row :gutter="20">
        <el-col v-for="product in likedProducts"
                :key="product.link"
                :xs="24"
                :sm="12"
                :md="8"
                :lg="6">
          <el-card class="product-card" :body-style="{ padding: '0px' }">
            <div class="product-image">
              <img :src="product.img" :alt="product.title">
              <div class="platform-tag">
                <svg-icon :icon-class="product.platform.toLowerCase()" />
                {{ product.platform }}
              </div>
            </div>

            <div class="product-info">
              <h3 class="product-title" :title="product.title">{{ product.title }}</h3>
              <div class="price-container">
                <span class="price">¥{{ product.price }}</span>
                <div v-if="product.change !== 0" class="price-change">
                  <el-tag v-if="product.change === -1"
                         type="success"
                         size="mini">
                    <i class="el-icon-caret-bottom" />
                    降价
                  </el-tag>
                  <el-tag v-else-if="product.change === 1"
                         type="danger"
                         size="mini">
                    <i class="el-icon-caret-top" />
                    涨价
                  </el-tag>
                </div>
              </div>

              <div class="shop-info">
                <span class="shop-name">{{ product.shop }}</span>
                <span class="sales">销量: {{ product.sales }}</span>
              </div>

              <div class="action-buttons">
                <a :href="product.link"
                   target="_blank"
                   class="el-button el-button--text"
                >
                  <i class="el-icon-view"></i>
                  查看详情
                </a>
                <el-button
                  type="text"
                  @click="viewPriceHistory(product.link)">
                  <i class="el-icon-data-line"></i>
                  历史价格
                </el-button>
                <el-button
                  type="text"
                  class="delete-btn"
                  @click="openDialog(product)">
                  <i class="el-icon-delete"></i>
                  取消收藏
                </el-button>
              </div>
            </div>
          </el-card>
        </el-col>
      </el-row>
    </div>

    <!-- 空状态展示 -->
    <el-empty v-if="likedProducts.length === 0"
              description="暂无收藏商品"
              :image-size="200">
      <el-button type="primary" @click="$router.push('/dashboard/index')">
        去逛逛
      </el-button>
    </el-empty>

    <el-dialog
      :visible.sync="dialogVisible"
      width="400px"
      center
      custom-class="unlike-dialog"
    >
      <template #title>
        <div class="dialog-title">
          <i class="el-icon-warning"></i>
          确认取消收藏
        </div>
      </template>

      <div class="dialog-content">
        <p class="product-name">{{ selectedProduct.title }}</p>
        <p class="confirm-text">确定要取消收藏这件商品吗？</p>
      </div>

      <span slot="footer" class="dialog-footer">
        <el-button plain @click="dialogVisible = false">取消</el-button>
        <el-button type="primary" @click="handleUnlike(selectedProduct)">确认</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  name: 'Like',

  data() {
    return {
      likedProducts: [],
      dialogVisible: false,
      selectedProduct: {}
    }
  },

  created() {
    this.fetchLikedProducts()
  },

  methods: {
    fetchLikedProducts() {
      axios.get('/compare/like/', {
        params: {
          user_id: this.$store.getters.id
        }
      }).then(response => {
        if (response.data.message === 'success') {
          this.likedProducts = response.data.products.map(product => ({
            ...product,
            change: Number(product.change) // 确保 change 是数字类型
          }))
        } else {
          this.$message.error('获取收藏商品失败')
        }
      }).catch(error => {
        console.error('获取收藏商品失败:', error)
        this.$message.error('获取收藏商品失败')
      })
    },

    handleUnlike(product) {
      axios.post('/compare/like/', {
        method: 'unlike',
        user_id: this.$store.getters.id,
        link: product.link
      }).then(response => {
        if (response.data === '成功取消收藏') {
          this.dialogVisible = false;
          this.$message.success('已取消收藏')
          this.likedProducts = this.likedProducts.filter(item => item.link !== product.link)
        } else {
          this.dialogVisible = false;
          this.$message.error('取消收藏失败')
        }
      }).catch(error => {
		this.dialogVisible = false;
        console.error('取消收藏失败:', error)
        this.$message.error('取消收藏失败')
      })
    },

    openDialog(product) {
      this.selectedProduct = product;
      this.dialogVisible = true;
    },

    viewPriceHistory(link) {
      this.$router.push({
        path: '/price/index',
        query: { link: link }
      })
    }
  }
}
</script>

<style lang="scss" scoped>
.like-container {
  padding: 20px;

  .like-header {
    margin-bottom: 20px;

    .header-content {
      display: flex;
      align-items: center;

      .title {
        font-size: 20px;
        font-weight: bold;
        color: #303133;
      }

      .subtitle {
        margin-left: 12px;
        font-size: 14px;
        color: #909399;
      }
    }
  }

  .products-grid {
    .product-card {
      height: 390px;
      margin-bottom: 20px;
      transition: all 0.3s;

      &:hover {
        transform: translateY(-5px);
        box-shadow: 0 6px 12px rgba(0,0,0,0.1);
      }

      .product-image {
        position: relative;
        height: 200px;
        overflow: hidden;

        img {
          width: 100%;
          height: 100%;
          object-fit: cover;
        }

        .platform-tag {
          position: absolute;
          top: 10px;
          right: 10px;
          padding: 4px 8px;
          background-color: rgba(0,0,0,0.6);
          color: white;
          border-radius: 4px;
          font-size: 12px;

          .svg-icon {
            margin-right: 4px;
          }
        }
      }

      .product-info {
        padding: 14px;

        .product-title {
          margin: 0 0 10px;
          font-size: 14px;
          line-height: 1.4;
          height: 40px;
          overflow: hidden;
          text-overflow: ellipsis;
          display: -webkit-box;
          -webkit-line-clamp: 2;
          -webkit-box-orient: vertical;
        }

        .price-container {
          display: flex;
          align-items: center;
          margin-bottom: 10px;

          .price {
            font-size: 20px;
            font-weight: bold;
            color: #f56c6c;
            margin-right: 8px;
          }

          .price-change {
            .el-tag {
              margin-left: 5px;

              i {
                margin-right: 2px;
              }
            }
          }
        }

        .shop-info {
          display: flex;
          justify-content: space-between;
          margin-bottom: 10px;
          font-size: 12px;
          color: #909399;
        }

        .action-buttons {
          display: flex;
          justify-content: space-between;
          border-top: 1px solid #ebeef5;
          padding-top: 10px;
          margin-top: 10px;

          .delete-btn {
            color: #f56c6c;

            &:hover {
              color: #f78989;
            }
          }

          .el-button {
            margin-right: 15px;

            &:last-child {
              margin-right: 0;
            }
          }

          a.el-button {
            display: inline-flex;
            align-items: center;
            justify-content: center;
            text-decoration: none;
            line-height: 1;
            white-space: nowrap;
            cursor: pointer;
            margin-right: 15px;

            i {
              margin-right: 4px;
            }

            &:hover {
              color: #409EFF;
            }

            &:last-child {
              margin-right: 0;
            }
          }
        }
      }
    }
  }

  .dialog-content {
    font-size: 16px;
    color: #333;
    margin-bottom: 20px;

    strong {
      color: #409EFF;
    }
  }

  .dialog-footer {
    display: flex;
    justify-content: flex-end;

    .el-button {
      margin-left: 10px;
    }
  }
}

::v-deep .unlike-dialog {
  border-radius: 12px;
  overflow: hidden;
  box-shadow: 0 20px 30px rgba(0, 0, 0, 0.2);

  // 添加对话框打开时的动画效果
  animation: dialogFadeIn 0.3s ease-out;

  @keyframes dialogFadeIn {
    from {
      opacity: 0;
      transform: translateY(-20px);
    }
    to {
      opacity: 1;
      transform: translateY(0);
    }
  }

  .el-dialog__header {
    padding: 20px 20px 10px;
    text-align: center;
    border-bottom: 1px solid #ebeef5;

    .dialog-title {
      font-size: 18px;
      font-weight: bold;
      color: #303133;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 8px;

      i {
        color: #f56c6c;
        font-size: 20px;

        // 添加警告图标的动画效果
        animation: warningShake 0.5s ease-in-out;
        
        @keyframes warningShake {
          0%, 100% { transform: rotate(0); }
          25% { transform: rotate(-10deg); }
          75% { transform: rotate(10deg); }
        }
      }
    }

    .el-dialog__headerbtn {
      top: 15px;
    }
  }

  .el-dialog__body {
    padding: 30px 25px;

    .dialog-content {
      text-align: center;

      .product-name {
        font-size: 15px;
        color: #409EFF;
        margin-bottom: 15px;
        line-height: 1.4;
        display: -webkit-box;
        -webkit-line-clamp: 2;
        -webkit-box-orient: vertical;
        overflow: hidden;

        // 添加文字渐变效果
        background: linear-gradient(45deg, #409EFF, #66b1ff);
        -webkit-background-clip: text;
        -webkit-text-fill-color: transparent;
        font-weight: 500;
      }

      .confirm-text {
        font-size: 14px;
        color: #606266;
        margin: 0;
      }
    }
  }

  .el-dialog__footer {
    padding: 10px 25px 20px;
    text-align: center;
    border-top: 1px solid #ebeef5;

    .dialog-footer {
      display: flex;
      justify-content: center;
      gap: 15px;

      .el-button {
        width: 120px;
        padding: 10px 20px;
        font-size: 14px;
        border-radius: 20px;
        transition: all 0.3s;

        &:hover {
          transform: translateY(-1px);
        }

        &--default {
          border-color: #dcdfe6;
          
          &:hover {
            border-color: #c6e2ff;
            color: #409EFF;
            background-color: #ecf5ff;
          }
        }

        &--primary {
          &:hover {
            background-color: #66b1ff;
            border-color: #66b1ff;
          }
        }

        // 添加按钮阴影效果
        box-shadow: 0 2px 6px rgba(0, 0, 0, 0.1);

        &:hover {
          box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15);
        }

        &--default {
          // 添加渐变边框效果
          background: linear-gradient(#fff, #fff) padding-box,
                     linear-gradient(45deg, #409EFF, #66b1ff) border-box;
          border: 1px solid transparent;
        }

        &--primary {
          // 添加渐变背景效果
          background: linear-gradient(45deg, #409EFF, #66b1ff);
          border: none;

          &:hover {
            background: linear-gradient(45deg, #66b1ff, #409EFF);
          }
        }
      }
    }
  }
}

// 移动端适配
@media screen and (max-width: 768px) {
  ::v-deep .unlike-dialog {
    width: 90% !important;
    margin: 0 auto;

    .el-dialog__body {
      padding: 20px;
    }

    .dialog-footer {
      .el-button {
        width: 100px;
        padding: 8px 15px;
      }
    }
  }
}
</style>
