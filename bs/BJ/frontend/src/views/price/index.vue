<template>
  <div class="dashboard-container">
    <div class="search-box">
      <div class="input-wrapper">
        <input
          type="text"
          placeholder="请输入商品的网页地址"
          v-model="searchQuery"
        />
        <button class="search-btn" @click="handleSearch">
          <img src="./search.png" alt="搜索">
        </button>
      </div>
    </div>

    <!-- 商品信息卡片 -->
    <el-card class="product-card" v-if="title" v-loading="loading">
      <div class="product-info">
        <!-- 图片部分 -->
        <div v-if="!img" class="product-image placeholder-image">
          <i class="el-icon-picture-outline" />
          <span>暂无图片</span>
        </div>
        <img v-else :src="img" class="product-image" :alt="title">

        <!-- 商品详情部分 -->
        <div class="product-details">
          <h2 class="product-title">{{ title }}</h2>

          <div class="platform-info">
            <svg-icon :icon-class="platform.toLowerCase()" />
            <span>{{ shop === '尚待查询' ? platform : shop }}</span>
          </div>

          <div class="sales-info" v-if="sales && sales !== '尚待查询'">
            <i class="el-icon-shopping-cart-2"></i>
            <span>销量：{{ sales }}</span>
          </div>

          <div class="action-buttons">
            <a :href="link"
               target="_blank"
               class="el-button el-button--primary"
            >
              <i class="el-icon-view"></i>
              查看商品
            </a>
            <el-button
              type="success"
              icon="el-icon-star-off"
              @click="handleLike">
              收藏商品
            </el-button>
          </div>
        </div>
      </div>
    </el-card>

    <!-- 添加价格趋势图 -->
    <el-card class="chart-card" v-if="price_history.length" v-loading="loading">
      <div ref="priceChart" class="price-chart"></div>
    </el-card>

    <!-- 添加无数据时的占位 -->
    <div v-if="loading && !title" class="loading-placeholder">
      <el-card class="placeholder-card" v-loading="true">
        <div style="height: 300px;"></div>
      </el-card>
    </div>
  </div>
</template>

<script>
import axios from "axios";
import * as echarts from 'echarts'

export default {
  data() {
    return {
      searchQuery: '',
      img: '',
      title: '',
      sales: '',
      shop: '',
      platform: '',
      link: '',
      price_history: [],
      chart: null,
      loading: false
    }
  },

  created() {
    // 从路由参数获取商品链接并执行搜索
    const link = this.$route.query.link
    if (link) {
      this.searchQuery = link
      this.handleSearch()
    }
  },

  methods: {
    handleSearch() {
      if (!this.searchQuery) {
        this.$message.warning('请输入商品链接')
        return
      }
      this.loading = true
      axios.get('/compare/price/', {
        params: {
          link: this.searchQuery,
          user_id: this.$store.getters.id
        }
      }).then(response => {
        const data = response.data
        if (data && data.length > 0) {
          // 获取商品基本信息（使用第一条记录）
          const productInfo = data[0]
          this.img = productInfo.img || ''
          this.title = productInfo.title
          this.sales = productInfo.sales === '尚待查询' ? '' : productInfo.sales
          this.shop = productInfo.shop === '尚待查询' ? productInfo.platform : productInfo.shop
          this.platform = productInfo.platform
          this.link = productInfo.link

          // 处理价格历史数据
          this.price_history = data
            .sort((a, b) => new Date(a.time) - new Date(b.time))
            .map(item => ({
              price: parseFloat(item.price),
              time: item.time
            }))

          this.$nextTick(() => {
            this.initChart()
          })
          this.$message.success('查询成功')
        } else {
          this.$message.warning('暂无该商品的价格记录')
        }
      }).catch(error => {
        console.error('查询失败:', error)
        this.$message.error('查询失败，请重试')
      }).finally(() => {
        this.loading = false
      })
    },

    initChart() {
      if (this.chart) {
        this.chart.dispose()
      }

      const formatTimeStr = (timeStr) => {
        return timeStr.replace('T', ' ').substring(0, 16)
      }

      const option = {
        title: {
          text: '商品价格走势',
          left: 'center'
        },
        tooltip: {
          trigger: 'axis',
          backgroundColor: 'rgba(255, 255, 255, 0.95)',
          borderColor: '#409EFF',
          borderWidth: 1,
          padding: [10, 15],
          textStyle: {
            color: '#606266',
            fontSize: 13
          },
          formatter: function(params) {
            const data = params[0]
            const timeStr = formatTimeStr(data.name)
            return `<div style="font-weight: bold; margin-bottom: 8px;">
                      <span style="color: #409EFF;">●</span> 价格记录
                    </div>
                    <div style="margin-bottom: 6px;">
                      时间：${timeStr}
                    </div>
                    <div style="font-size: 14px; font-weight: bold; color: #f56c6c;">
                      价格：¥${data.value.toFixed(2)}
                    </div>`
          },
          axisPointer: {
            type: 'cross',
            snap: true,
            label: {
              show: false
            },
            crossStyle: {
              color: '#409EFF',
              width: 1,
              type: 'dashed'
            }
          }
        },
        grid: {
          top: 60,
          left: 60,
          right: 60,
          bottom: 60
        },
        xAxis: {
          type: 'category',
          splitLine: {
            show: false
          },
          axisLine: {
            lineStyle: {
              color: '#ddd'
            }
          },
          data: this.price_history.map(item => item.time),
          axisLabel: {
            color: '#666',
            formatter: function(value) {
              return formatTimeStr(value)
            }
          },
          axisPointer: {
            show: true,
            label: {
              show: false
            }
          }
        },
        yAxis: {
          type: 'value',
          axisLabel: {
            formatter: '¥{value}',
            color: '#666'
          },
          splitLine: {
            show: true,
            lineStyle: {
              type: 'dashed',
              color: '#eee'
            }
          },
          axisPointer: {
            show: true,
            label: {
              show: false
            }
          }
        },
        series: [{
          name: '价格',
          type: 'line',
          data: this.price_history.map(item => item.price),
          smooth: false,
          showSymbol: true,
          symbol: 'circle',
          symbolSize: 6,
          emphasis: {
            scale: true,
            focus: 'series',
            itemStyle: {
              color: '#fff',
              borderColor: '#409EFF',
              borderWidth: 2
            },
            label: {
              show: true,
              formatter: '¥{c}',
              position: 'top'
            }
          },
          itemStyle: {
            color: '#409EFF',
            borderColor: '#fff',
            borderWidth: 1
          },
          lineStyle: {
            width: 3,
            color: '#409EFF'
          },
          areaStyle: {
            color: new echarts.graphic.LinearGradient(0, 0, 0, 1, [{
              offset: 0,
              color: 'rgba(64,158,255,0.3)'
            }, {
              offset: 1,
              color: 'rgba(64,158,255,0.1)'
            }])
          }
        }]
      }

      const chart = echarts.init(this.$refs.priceChart)

      chart.on('mouseover', (params) => {
        if (params.componentType === 'series') {
          chart.setOption({
            tooltip: {
              axisPointer: {
                type: 'cross',
                label: {
                  show: true,
                  backgroundColor: '#409EFF'
                }
              }
            }
          })
        }
      })

      chart.on('mouseout', () => {
        chart.setOption({
          tooltip: {
            axisPointer: {
              type: 'none'
            }
          }
        })
      })

      chart.setOption(option)

      window.addEventListener('resize', () => {
        chart && chart.resize()
      })

      this.chart = chart
    },

    handleLike() {
      axios.post('/compare/like/', {
        method: 'like',
        user_id: this.$store.getters.id,
        img: this.img,
        title: this.title,
        price: this.price_history[this.price_history.length - 1].price, // 使用最新价格
        sales: this.sales,
        shop: this.shop,
        platform: this.platform,
        link: this.link,
        time: this.price_history[this.price_history.length - 1].time // 使用最新时间
      }).then(response => {
        if (response.data === '成功收藏') {
          this.$message.success(response.data)
        } else if (response.data === '已收藏该商品') {
          this.$message.warning(response.data)
        } else {
          this.$message.error('收藏失败')
        }
      }).catch(error => {
        console.error('收藏失败:', error)
        this.$message.error('收藏失败，请重试')
      })
    }
  },

  beforeDestroy() {
    if (this.chart) {
      this.chart.dispose()
      window.removeEventListener('resize', this.chart.resize)
    }
  }
}
</script>

<style lang="scss" scoped>
.dashboard-container {
  padding: 20px;

  .search-box {
    margin: 50px auto auto;
    max-width: 600px;
    padding: 0 20px;

    .input-wrapper {
      position: relative;
      width: 100%;
      height: 50px;
      background-color: #ffffff;
      border-radius: 25px;
      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
      display: flex;
      align-items: center;
      padding-right: 50px;

      input {
        flex: 1;
        height: 100%;
        padding: 0 20px;
        border: none;
        background: none;
        outline: none;
        color: #333;
        font-size: 16px;
        width: 100%;
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap;
      }

      .search-btn {
        position: absolute;
        right: 0;
        top: 50%;
        transform: translateY(-50%);
        width: 50px;
        height: 50px;
        background: none;
        border: none;
        cursor: pointer;
        outline: none;
        display: flex;
        align-items: center;
        justify-content: center;
        transition: all 0.3s ease;

        &:hover {
          opacity: 0.8;
        }

        img {
          width: 24px;
          height: 24px;
        }
      }
    }
  }

  @media screen and (max-width: 768px) {
    .search-box {
      margin: 30px auto;
      padding: 0 15px;

      .input-wrapper {
        height: 45px;

        input {
          font-size: 14px;
        }

        .search-btn {
          width: 45px;
          height: 45px;

          img {
            width: 20px;
            height: 20px;
          }
        }
      }
    }
  }

  .product-card {
    margin: 20px auto;
    max-width: 800px;
    border-radius: 8px;
    box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);

    .product-info {
      display: flex;
      gap: 24px;
      padding: 20px;

      .product-image,
      .placeholder-image {
        width: 240px;
        height: 240px;
        border-radius: 8px;
        overflow: hidden;
      }

      .product-image {
        object-fit: contain;
        background-color: #f5f7fa;
      }

      .placeholder-image {
        background-color: #f5f7fa;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        color: #909399;

        i {
          font-size: 48px;
          margin-bottom: 12px;
        }

        span {
          font-size: 14px;
        }
      }

      .product-details {
        flex: 1;
        display: flex;
        flex-direction: column;

        .product-title {
          margin: 0 0 20px;
          font-size: 20px;
          line-height: 1.4;
          color: #303133;
          display: -webkit-box;
          -webkit-line-clamp: 2;
          -webkit-box-orient: vertical;
          overflow: hidden;
          text-overflow: ellipsis;
        }

        .platform-info,
        .sales-info {
          display: flex;
          align-items: center;
          gap: 8px;
          margin-bottom: 16px;
          color: #606266;
          font-size: 14px;

          .svg-icon {
            font-size: 16px;
          }

          i {
            font-size: 16px;
            color: #409EFF;
          }
        }

        .action-buttons {
          margin-top: auto;
          display: flex;
          gap: 12px;

          .el-button {
            flex: 1;  // 让按钮等宽
            padding: 10px 20px;
            border-radius: 20px;

            i {
              margin-right: 4px;
            }

            &:hover {
              transform: translateY(-1px);
              box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
            }
          }
        }
      }
    }
  }

  // 响应式布局
  @media screen and (max-width: 768px) {
    .product-card {
      margin: 20px 10px;

      .product-info {
        flex-direction: column;
        padding: 16px;

        .product-image,
        .placeholder-image {
          width: 100%;
          height: 200px;
          margin: 0 auto;
        }

        .product-details {
          .product-title {
            font-size: 18px;
            margin-bottom: 16px;
          }

          .action-buttons {
            flex-wrap: wrap;

            .el-button {
              width: 100%;
            }
          }
        }
      }
    }
  }

  .chart-card {
    margin: 20px auto;
    max-width: 800px;

    .price-chart {
      height: 400px;
      width: 100%;
    }
  }

  .loading-placeholder {
    margin: 20px auto;
    max-width: 800px;

    .placeholder-card {
      border-radius: 8px;
      box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
    }
  }
}

.action-buttons {
  a.el-button {
    display: inline-flex;
    align-items: center;
    justify-content: center;
    text-decoration: none;
    line-height: 1;
    white-space: nowrap;
    cursor: pointer;

    i {
      margin-right: 4px;
    }
  }
}

// 自定义加载样式
::v-deep .el-loading-mask {
  background-color: rgba(255, 255, 255, 0.8);

  .el-loading-spinner {
    .circular {
      width: 42px;
      height: 42px;
    }

    .el-loading-text {
      color: #409EFF;
      margin-top: 8px;
      font-size: 14px;
    }
  }
}
</style>
