<template>
  <div class="dashboard-container">
    <div class="search-container">
      <div class="search-box">
        <form>
          <el-autocomplete
            ref="autocomplete"
            v-model="productName"
            :fetch-suggestions="querySearchAsync"
            placeholder="探索你心仪的商品吧..."
            :trigger-on-focus="false"
            clearable
            popper-class="my-autocomplete"
            class="custom-autocomplete"
            @select="handleSelect"
          >
            <template slot-scope="{ item }">
              <div class="suggestion-item">
                {{ item.value }}
              </div>
            </template>
          </el-autocomplete>
          <button class="search-btn" type="submit" @click.prevent="checkLogin()">
            <img src="./search.png" alt="搜索">
          </button>
        </form>
      </div>
      <div class="filter-toggle" @click="isFilterVisible = !isFilterVisible">
        <i :class="['el-icon-arrow-down', { 'is-active': isFilterVisible }]"></i>
        筛选
      </div>
    </div>

    <el-collapse-transition>
      <el-card v-show="isFilterVisible" class="filter-card" :body-style="{ padding: '20px' }">
        <el-row :gutter="30">
          <!-- 平台选择 -->
          <el-col :span="24" :sm="24" :md="8" class="filter-item">
            <div class="filter-label">
              <i class="el-icon-shopping-bag-1"></i>
              平台选择
            </div>
            <el-checkbox-group v-model="selectedPlatforms" class="platform-checkboxes">
              <el-checkbox label="京东">
                <svg-icon icon-class="jd" style="margin-right: 4px"/>京东
              </el-checkbox>
              <el-checkbox label="唯品会">
                <svg-icon icon-class="vip" style="margin-right: 4px"/>唯品会
              </el-checkbox>
              <el-checkbox label="苏宁">
                <svg-icon icon-class="sn" style="margin-right: 4px"/>苏宁易购
              </el-checkbox>
            </el-checkbox-group>
          </el-col>

          <!-- 价格区间 -->
          <el-col :span="24" :sm="24" :md="8" class="filter-item">
            <div class="filter-label">
              <i class="el-icon-money"></i>
              价格区间
            </div>
            <div class="price-range">
              <el-input
                v-model="priceRange[0]"
                placeholder="最低价"
                class="price-input"
                @input="handlePriceChange"
              >
                <template slot="prefix">¥</template>
              </el-input>
              <span class="price-separator">-</span>
              <el-input
                v-model="priceRange[1]"
                placeholder="最高价"
                class="price-input"
                @input="handlePriceChange"
              >
                <template slot="prefix">¥</template>
              </el-input>
            </div>
          </el-col>

          <!-- 排序按钮 -->
          <el-col :span="24" :sm="24" :md="8" class="filter-item">
            <div class="filter-label">
              <i class="el-icon-sort"></i>
              价格排序
            </div>
            <div class="sort-buttons">
              <el-button
                :class="{ active: sortType === 'low' }"
                @click="sortProducts('low')"
              >
                <i class="el-icon-top"></i>
                从低到高
              </el-button>
              <el-button
                :class="{ active: sortType === 'high' }"
                @click="sortProducts('high')"
              >
                <i class="el-icon-bottom"></i>
                从高到低
              </el-button>
            </div>
          </el-col>
        </el-row>
      </el-card>
    </el-collapse-transition>

    <el-dialog :visible.sync="jd_card" center>
      <template #title>
        <div>
          <svg-icon icon-class="wechat"/> 使用微信扫一扫登录
        </div>
        <div style="font-weight: bold; font-size: 22px; margin-top: 16px;">
          「 京东 」
        </div>
      </template>
      <img :src="jd_qrcode === '' ? require('./qrcode.png') : jd_qrcode" alt="微信扫码登录" style="clear: both; display: block; margin: auto; width: 50%;">
      <template #footer>
        <div style="font-size: 13px">
        （取消扫码则跳过京东的搜索结果）
        </div>
      </template>
    </el-dialog>

    <el-dialog :visible.sync="vip_card" center>
      <template #title>
        <div>
          <svg-icon icon-class="wechat"/> 使用微信扫一扫登录
        </div>
        <div style="font-weight: bold; font-size: 22px; margin-top: 16px;">
          「 唯品会 」
        </div>
      </template>
      <img :src="vip_qrcode === '' ? require('./qrcode.png') : vip_qrcode" alt="微信扫码登录" style="clear: both; display: block; margin: auto; width: 50%;">
      <template #footer>
        <div style="font-size: 13px">
        （取消扫码则跳过唯品会的搜索结果）
        </div>
      </template>
    </el-dialog>

    <el-dialog :visible.sync="sn_card" center>
      <template #title>
        <div>
          <svg-icon icon-class="wechat"/> 使用微信扫一扫登录
        </div>
        <div style="font-weight: bold; font-size: 22px; margin-top: 16px;">
          「 苏宁易购 」
        </div>
      </template>
      <img :src="sn_qrcode === '' ? require('./qrcode.png') : sn_qrcode" alt="微信扫码登录" style="clear: both; display: block; margin: auto; width: 50%;">
      <template #footer>
        <div style="font-size: 13px">
        （取消扫码则跳过苏宁易购的搜索结果）
        </div>
      </template>
    </el-dialog>

    <div class="products">
    <el-row>
      <el-col :span="6" :xs="24" v-for="product in filteredProducts" :key="product.title" style="display: flex; justify-content: center;">
        <el-card class="product-card" :body-style="{ padding: '0' }">
          <div class="product-image-wrapper">
            <img :src="product.img" class="product-image" alt="商品图片">
            <div class="platform-tag">
              <svg-icon :icon-class='product.platform'/>
              {{ product.platform }}
            </div>
          </div>
          <div class="product-content">
            <div class="price-section">
              <span class="price-symbol">¥</span>
              <span class="price-value">{{ product.price }}</span>
            </div>
            <div class="title-section">{{ product.title }}</div>
            <div class="info-section">
              <span class="sales-info">
                <i class="el-icon-shopping-cart-2"></i>
                已售 {{ product.sales }}
              </span>
              <span class="shop-info">
                <i class="el-icon-goods"></i>
                {{ product.shop }}
              </span>
            </div>
            <div class="action-section">
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
                  @click="handleLike(product)">
                  <i class="el-icon-star-off"></i>
                  收藏
                </el-button>
              </div>
            </div>
          </div>
        </el-card>
      </el-col>
    </el-row>
    </div>

    <div v-if="pageCount > 1" class="pagination-container" style="text-align: center; margin: 20px 0;">
      <button
        class="page-button1"
        :disabled="currentPage === 1"
        @click="changePage(currentPage - 1)"
      >
        <span>上一页</span>
      </button>
      <span style="margin: 0 15px;">
        第 {{ currentPage }} 页，共 {{ pageCount }} 页 (共 {{ filteredTotal }} 条)
      </span>
      <button
        class="page-button2"
        :disabled="currentPage === pageCount"
        @click="changePage(currentPage + 1)"
      >
        <span>下一页</span>
      </button>
    </div>
  </div>
</template>

<script>

import axios from "axios";
import request from '@/utils/request'
import debounce from 'lodash/debounce'

export default {
  data() {
    return {
      currentPage: 1, // 当前页码
      pageSize: 8, // 每页显示的产品数量
      allPlatforms: ['京东', '唯品会', '苏宁'],
      selectedPlatforms: [],
      productName: '',
      products: [
        // {
        //   img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
        //   title: '毒蝰v3pro',
        //   price: '1699',
        //   sales: '10000+',
        //   shop: '雷蛇京东自营店',
        //   platform: '京东',
        //   link: 'https://item.jd.com/10101957501630.html',
        //   time: '2024-10-11 16:16'
        // },{
        //   img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
        //   title: '毒蝰v3pro',
        //   price: '1499',
        //   sales: '10000+',
        //   shop: '雷蛇京东自营店',
        //   platform: '京东',
        //   link: 'https://item.jd.com/10101957501630.html',
        //   time: '2024-10-11 16:16'
        // },{
        //   img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
        //   title: '毒蝰v3pro',
        //   price: '1299',
        //   sales: '10000+',
        //   shop: '雷蛇京东自营店',
        //   platform: '京东',
        //   link: 'https://item.jd.com/10101957501630.html',
        //   time: '2024-10-11 16:16'
        // },{
        //   img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
        //   title: '毒蝰v3pro',
        //   price: '1399',
        //   sales: '10000+',
        //   shop: '雷蛇京东自营店',
        //   platform: '京东',
        //   link: 'https://item.jd.com/10101957501630.html',
        //   time: '2024-10-11 16:16'
        // },{
        //   img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
        //   title: '毒蝰v3pro',
        //   price: '1599',
        //   sales: '10000+',
        //   shop: '雷蛇京东自营店',
        //   platform: '京东',
        //   link: 'https://item.jd.com/10101957501630.html',
        //   time: '2024-10-11 16:16'
        // },
      ],
      loading: null,

      jd_timer: null,
      jd_qrcode: '',
      jd_card: false,
      jd_check: '',

      vip_timer: null,
      vip_qrcode: '',
      vip_card: false,
      vip_check: '',

      sn_timer: null,
      sn_qrcode: '',
      sn_card: false,
      sn_check: '',

      priceRange: ['', ''], // 价格范围
      sortType: 'default', // 排序方式
      filteredTotal: 0, // 添加这个属性用于存储筛选后的商品总数
      isFilterVisible: false // 添加控制筛选面板显示的状态
    }
  },
  computed: {
    filteredProducts() {
      // 先获取经过平台和价格筛选的所有商品
      const selectedPlatforms = this.selectedPlatforms.length === 0 ? this.allPlatforms : this.selectedPlatforms
      const [minPrice, maxPrice] = this.priceRange.map(range => range === '' ? null : parseFloat(range))

      // 筛选商品
      let filteredAndSortedProducts = this.products.filter(product =>
        selectedPlatforms.includes(product.platform) &&
        (minPrice === null || parseFloat(product.price) >= minPrice) &&
        (maxPrice === null || parseFloat(product.price) <= maxPrice)
      )

      // 排序
      if (this.sortType === 'low') {
        filteredAndSortedProducts = filteredAndSortedProducts.sort((a, b) => parseFloat(a.price) - parseFloat(b.price))
      } else if (this.sortType === 'high') {
        filteredAndSortedProducts = filteredAndSortedProducts.sort((a, b) => parseFloat(b.price) - parseFloat(a.price))
      }

      // 存储筛选后的总商品数，用于计算总页数
      this.filteredTotal = filteredAndSortedProducts.length

      // 分页
      const start = (this.currentPage - 1) * this.pageSize
      const end = this.currentPage * this.pageSize
      return filteredAndSortedProducts.slice(start, end)
    },

    pageCount() {
      if (this.filteredTotal === 0) {
        return 1
      }
      return Math.ceil(this.filteredTotal / this.pageSize)
    }
  },

  watch: {

    jd_card(newVal, oldVal) {
      if (newVal === false && oldVal === true) {
        this.jd_qrcode = ''
        if(this.jd_timer) {
          clearTimeout(this.jd_timer)
          this.jd_timer = null
        }
        if (this.vip_check === 'false') {
          this.vip_card = true
          this.vipLogin()
        }
        else if (this.sn_check === 'false') {
          this.sn_card = true
          this.snLogin()
        }
        else {
          this.loading.close()
          this.loading = this.$loading({fullscreen: false, text: '稍等一下下，马上就加载出来啦...', target: '.dashboard-container'})
          this.Search()
        }
      }
    },

    vip_card(newVal, oldVal) {
      if (newVal === false && oldVal === true) {
        this.vip_qrcode = ''
        if(this.vip_timer) {
          clearTimeout(this.vip_timer)
          this.vip_timer = null
        }
        if (this.sn_check === 'false') {
          this.sn_card = true
          this.snLogin()
        }
        else {
          this.loading.close()
          this.loading = this.$loading({fullscreen: false, text: '稍等一下下，马上就加载出来啦...', target: '.dashboard-container'})
          this.Search()
        }
      }
    },

    sn_card(newVal, oldVal) {
      if (newVal === false && oldVal === true) {
        this.sn_qrcode = ''
        if(this.sn_timer) {
          clearTimeout(this.sn_timer)
          this.sn_timer = null
        }
        this.loading.close()
        this.loading = this.$loading({fullscreen: false, text: '稍等一下下，马上就加载出来啦...', target: '.dashboard-container'})
        this.Search()
      }
    },

    // 添加监听器，当筛选条件改变时，重置页码到第一页
    selectedPlatforms() {
      this.currentPage = 1
    },
    priceRange: {
      handler() {
        this.currentPage = 1
      },
      deep: true
    },
    sortType() {
      this.currentPage = 1
    },

    // 监听商品数量变化
    'products.length': {
      handler(newLength) {
        if (newLength === 0) {
          this.currentPage = 1
        }
      },
      immediate: true
    }

  },

  mounted() {

  },

  methods: {
    changePage(page) {
      // 添加边界检查
      if (page < 1) {
        page = 1
      } else if (page > this.pageCount) {
        page = this.pageCount
      }
      this.currentPage = page
    },

    handlePriceChange() {
      // 确保最高价不小于最低价
      const [minPrice, maxPrice] = this.priceRange.map(range => range === '' ? null : parseFloat(range));
      if (minPrice !== null && maxPrice !== null && minPrice > maxPrice) {
        this.priceRange[0] = this.priceRange[1];
      }
    },

    sortProducts(type) {
      this.sortType = type;
    },

    // 搜索商品
    checkLogin() {
      // 关闭词条推荐
      if (this.$refs.autocomplete) {
        this.$refs.autocomplete.close()
      }

      this.loading = this.$loading({
        fullscreen: true,
        text: '稍等一下下，马上就加载出来啦...',
        target: '.dashboard-container'
      })
      axios.get('/compare/dashboard/', {
        params: {
          method: 'check',
          user_id: this.$store.getters.id,
        }
      }).then(response => {
        let res = response.data
        this.jd_check = res.jd
        this.vip_check = res.vip
        this.sn_check = res.sn
        if (this.jd_check === 'false') {
          this.loading.close()
          this.jd_card = true
          this.jdLogin()
        }
        else if (this.vip_check === 'false') {
          this.loading.close()
          this.vip_card = true
          this.vipLogin()
        }
        else if (this.sn_check === 'false') {
          this.loading.close()
          this.sn_card = true
          this.snLogin()
        }
        else
          this.Search()
      })
    },

    jdLogin() {
      axios.get('/compare/dashboard/', {
        params: {
          method: 'jd_login',
          user_id:this.$store.getters.id,
        }
      }).then(response => {
        let res = response.data
        if (res.message === '待扫码') {
          if (this.jd_card === false)
            return
          this.jd_qrcode = res.qrcode
          this.jd_card = true
          this.jd_timer = setTimeout(this.jdLogin, 8000)
        }
        else if (res.message === '扫码成功') {
          this.jd_card = false
          this.$message.success('扫码成功')
        }
        else {
          this.$message.error('扫码失败，请重新搜索')
          console.log(res.message)
        }
      })
    },

    vipLogin() {
      axios.get('/compare/dashboard/', {
        params: {
          method: 'vip_login',
          user_id:this.$store.getters.id,
        }
      }).then(response => {
        let res = response.data
        if (res.message === '待扫码') {
          if (this.vip_card === false)
            return
          this.vip_qrcode = res.qrcode
          this.vip_card = true
          this.vip_timer = setTimeout(this.vipLogin, 8000)
        }
        else if (res.message === '扫码成功') {
          this.vip_card = false
          this.$message.success('扫码成功')
        }
        else {
          this.$message.error('扫码失败，请重新搜索')
          console.log(res.message)
        }
      })
    },

    snLogin() {
      axios.get('/compare/dashboard/', {
        params: {
          method: 'sn_login',
          user_id:this.$store.getters.id,
        }
      }).then(response => {
        let res = response.data
        if (res.message === '待扫码') {
          if (this.sn_card === false)
            return
          this.sn_qrcode = res.qrcode
          this.sn_card = true
          this.sn_timer = setTimeout(this.snLogin, 8000)
        }
        else if (res.message === '扫码成功') {
          this.sn_card = false
          this.$message.success('扫码成功')
        }
        else {
          this.$message.error('扫码失败，请重新搜索')
          console.log(res.message)
        }
      })
    },

    Search() {
      // this.$message.success('查询中，请稍等')
      Promise.allSettled([
        axios.get('/compare/dashboard/', {params: {method: 'jd_search', user_id:this.$store.getters.id, name:this.productName}}),
        axios.get('/compare/dashboard/', {params: {method: 'vip_search', user_id:this.$store.getters.id, name:this.productName}}),
        axios.get('/compare/dashboard/', {params: {method: 'sn_search', user_id:this.$store.getters.id, name:this.productName}}),
      ]).then(responses => {
        this.products = []
        responses.forEach(response => {
          if (response.status === 'fulfilled') {
            let res = response.value.data
            if (res.message === 'success')
              this.products = this.products.concat(res.products)
          }
          else
            console.log(response.reason)
        })
        this.loading.close()
        this.$message.success('成功查询')
      }).catch(error => {
        console.log('Error fetching data:', error)
        this.$message.error('查询失败，请重试')
      })
    },

    handleLike(product) {
      axios.post('/compare/like/', {
        method: 'like',
        user_id: this.$store.getters.id,
        img: product.img,
        title: product.title,
        price: product.price,
        sales: product.sales,
        shop: product.shop,
        platform: product.platform,
        link: product.link,
        time: product.time
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
    },

    viewPriceHistory(link) {
      this.$router.push({
        path: '/price/index',
        query: { link: link }
      })
    },

    // 修改搜索建议的方法
    async querySearchAsync(queryString, callback) {
      if (queryString.length === 0) {
        callback([])
        return
      }

      try {
        let response = await request({
          url: '/compare/search/suggestions/',
          method: 'get',
          params: {
            keywords: queryString
          }
        })
        response = response.data
        console.log(response)
        if (response.error_code === 0) {
          const suggestions = response.data.map(item => ({
            value: item
          }))
          callback(suggestions)
        } else {
          callback([])
        }
      } catch (error) {
        console.error('获取搜索建议失败:', error)
        callback([])
      }
    },

    // 处理选中建议项
    handleSelect(item) {
      this.productName = item.value
      // 关闭词条推荐
      if (this.$refs.autocomplete) {
        this.$refs.autocomplete.close()
      }
      this.checkLogin()
    }
  },

  // 添加 beforeRouteLeave 钩子
  beforeRouteLeave(to, from, next) {
    // 将当前搜索状态保存到 sessionStorage
    sessionStorage.setItem('dashboardState', JSON.stringify({
      products: this.products,
      productName: this.productName,
      currentPage: this.currentPage,
      selectedPlatforms: this.selectedPlatforms,
      priceRange: this.priceRange,
      sortType: this.sortType
    }))
    next()
  },

  created() {
    // 尝试从 sessionStorage 恢复状态
    const savedState = sessionStorage.getItem('dashboardState')
    if (savedState) {
      const state = JSON.parse(savedState)
      this.products = state.products
      this.productName = state.productName
      this.currentPage = state.currentPage
      this.selectedPlatforms = state.selectedPlatforms
      this.priceRange = state.priceRange
      this.sortType = state.sortType
    }

    // 使用 debounce 防抖，避免频繁请求
    this.debouncedQuerySearch = debounce(this.querySearchAsync, 300)
  }
}
</script>

<style lang="scss" scoped>
.dashboard-container {
  .search-container {
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 15px;
    margin: 50px auto 20px;
    width: 600px;

    @media screen and (max-width: 768px) {
      width: 90%;
      margin: 20px auto;
      flex-direction: row; // 改为水平排列
      flex-wrap: wrap; // 允许换行

      .search-box {
        width: calc(100% - 30px); // 减去筛选按钮的宽度和间距
        min-width: 0; // 允许搜索框缩小
      }

      .filter-toggle {
        padding: 6px 12px;
        height: 30px;
      }
    }
  }

  .search-box {
    flex: 1;
    position: relative;
    height: 50px;
    background-color: #ffffff;
    border-radius: 25px;
    overflow: visible;
    display: flex;
    align-items: center;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);

    form {
      width: 100%; // 确保表单占满容器
    }

    ::v-deep .custom-autocomplete {
      width: 100%;
      height: 100%;

      .el-input__inner {
        width: 100%;
        height: 100%;
        padding: 0 60px 0 20px;
        border: none;
        background: none;
        outline: none;
        color: #333;
        font-size: 16px;
      }

      .el-input__suffix {
        display: none;
      }
    }

    .search-btn {
      position: absolute;
      right: 0;
      top: 2px;
      width: 50px;
      height: 50px;
      background: none;
      border: none;
      cursor: pointer;
      outline: none;

      img {
        width: 80%;
        height: auto;
      }
    }
  }

  .filter-toggle {
    display: inline-flex;
    align-items: center;
    padding: 8px 16px;
    font-size: 13px;
    color: #606266;
    background: #f5f7fa;
    border-radius: 20px;
    cursor: pointer;
    transition: all 0.3s;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.05);
    height: 34px;
    white-space: nowrap;

    i {
      margin-right: 4px;
      transition: transform 0.3s;
      font-size: 12px;

      &.is-active {
        transform: rotate(180deg);
      }
    }

    &:hover {
      background: #ecf5ff;
      color: #409EFF;
    }
  }

  .filter-card {
    width: 80%;
    margin: 10px auto 20px;
    border-radius: 8px;
    box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.05);

    .filter-item {
      margin-bottom: 15px;

      &:last-child {
        margin-bottom: 0;
      }

      .filter-label {
        font-size: 13px;
        color: #606266;
        margin-bottom: 10px;
        display: flex;
        align-items: center;

        i {
          margin-right: 4px;
          font-size: 14px;
        }
      }

      .price-range {
        display: flex;
        align-items: center;
        gap: 10px;

        .price-input {
          width: 120px;

          ::v-deep .el-input__inner {
            text-align: center;
            padding-left: 25px;
          }

          ::v-deep .el-input__prefix {
            left: 10px;
            color: #909399;
            height: 100%;
            display: flex;
            align-items: center;
          }
        }

        .price-separator {
          color: #909399;
          font-weight: bold;
        }
      }
    }
  }

  .product-card {
    margin-bottom: 20px;
    transition: all 0.3s;
    border-radius: 12px;
    overflow: hidden;
    width: 320px;
    height: 450px;

    &:hover {
      transform: translateY(-5px);
      box-shadow: 0 6px 16px rgba(0, 0, 0, 0.1);
    }

    .product-image-wrapper {
      position: relative;
      height: 200px;
      overflow: hidden;

      .product-image {
        width: 100%;
        height: 100%;
        object-fit: cover;
        transition: transform 0.3s;

        &:hover {
          transform: scale(1.05);
        }
      }

      .platform-tag {
        position: absolute;
        top: 10px;
        right: 10px;
        padding: 4px 8px;
        background: rgba(0, 0, 0, 0.6);
        color: white;
        border-radius: 4px;
        font-size: 12px;
        display: flex;
        align-items: center;
        gap: 4px;
      }
    }

    .product-content {
      padding: 16px;

      .price-section {
        margin-bottom: 10px;

        .price-symbol {
          color: #f56c6c;
          font-size: 16px;
          margin-right: 2px;
        }

        .price-value {
          color: #f56c6c;
          font-size: 24px;
          font-weight: bold;
        }
      }

      .title-section {
        font-size: 14px;
        line-height: 1.4;
        height: 40px;
        overflow: hidden;
        text-overflow: ellipsis;
        display: -webkit-box;
        -webkit-line-clamp: 2;
        -webkit-box-orient: vertical;
        margin-bottom: 10px;
        color: #303133;
      }

      .info-section {
        display: flex;
        justify-content: space-between;
        margin-bottom: 15px;
        font-size: 12px;
        color: #909399;

        //.sales-info, .shop-info {
        //  display: flex;
        //  align-items: center;
        //  gap: 4px;
        //}
        .shop-info {
          flex: 1;
          //display: flex; /* 使用 Flexbox 布局 */
          justify-content: right; /* 使内容两端对齐 */
          align-items: flex-end; /* 垂直居中对齐 */
          overflow: hidden; /* 隐藏溢出内容 */
          //white-space: nowrap; /* 防止换行 */
          text-overflow: ellipsis; /* 超出部分用省略号表示 */
          width: 100%; /* 确保占满父容器宽度 */
        }

        .sales-info {
          flex: 1; /* 允许商店名称占用剩余空间 */
          //margin-right: 10px; /* 添加右边距以分隔销售信息 */
          //overflow: hidden; /* 隐藏溢出内容 */
          white-space: nowrap; /* 防止换行 */
          //text-overflow: ellipsis; /* 超出部分用省略号表示 */
        }
      }

      .action-section {
        border-top: 1px solid #f0f0f0;
        padding-top: 15px;
        margin-top: 15px;

        .action-buttons {
          display: flex;
          align-items: center;
          justify-content: space-between;
          width: 100%;

          .action-btn {
            flex: 1;
            padding: 0;
            height: 32px;
            font-size: 13px;
            display: flex;
            align-items: center;
            justify-content: center;
            transition: all 0.3s;

            i {
              margin-right: 4px;
              font-size: 14px;
            }

            &:hover {
              color: #409EFF;
              transform: translateY(-1px);
            }

            &.like-btn {
              &:hover {
                color: #f56c6c;
              }
            }
          }

          .el-divider--vertical {
            height: 16px;
            margin: 0;
          }
        }
      }
    }
  }

  .product-detail-link {
    display: inline-block;
    margin-top: 10px;
    font-size: 14px;
    color: #9ea0a1; /* Element UI 主题色 */
    text-decoration: none; /* 去除下划线 */
  }

  .product-detail-link:hover {
    text-decoration: underline; /* 鼠标悬停时添加下划线 */
  }

  ::v-deep .el-dialog {
    width: 25%;
  }

  ::v-deep .el-dialog .el-dialog__body{
    flex:1;
    overflow: auto;
    padding-top: 0;
    padding-bottom: 0;
  }

  .products {
    @media screen and (max-width: 768px) {
      padding: 0 10px;

      .el-row {
        margin: 0 !important;
      }

      .el-col {
        width: 100%;
        padding: 0 !important;
      }

      .product-card {
        width: 100%;
        max-width: none;
        margin: 0 auto 15px;
        height: auto; // 让卡片高度自适应

        .product-content {
          padding: 15px;
          height: auto; // 让内容区域高度自适应
          display: flex;
          flex-direction: column;

          .action-section {
            margin-top: 10px;

            .action-buttons {
              display: flex;
              justify-content: space-between;
              padding: 10px 0;
              gap: 5px;
              height: auto; // 确保按钮区域高度自适应

              a.el-button,
              .el-button {
                height: auto; // 让按钮高度自适应
                min-height: 40px; // 设置最小高度确保可点击
                padding: 5px;
                white-space: normal; // 允许文字换行

                i {
                  display: block;
                  margin: 0 auto 4px;
                }
              }
            }
          }
        }
      }
    }
  }

   .page-button1 {
        display: inline-block;
        border-radius: 20px;
        background-color: #72d1b2;
        border: none;
        color: #ffff;
        text-align: center;
        font-size: 16px;
        font-weight: 400;
        padding: 12px;
        width: 120px;
        transition: all 0.5s;
        cursor: pointer;
        margin: 5px;
        vertical-align: middle;
      }

      .page-button1 span {
        cursor: pointer;
        display: inline-block;
        position: relative;
        transition: 0.5s;
      }

      .page-button1 span::before {
        content: "<<";
        position: absolute;
        opacity: 0;
        top: 0;
        left: -20px;
        transition: 0.5s;
      }

      .page-button1:hover span {
        padding-left: 30px;
      }

      .page-button1:hover span::before {
        opacity: 1;
        left: 0;
      }

   .page-button2 {
        display: inline-block;
        border-radius: 20px;
        background-color: #a181d5;
        border: none;
        color: #ffff;
        text-align: center;
        font-size: 16px;
        font-weight: 400;
        padding: 12px;
        width: 120px;
        transition: all 0.5s;
        cursor: pointer;
        margin: 5px;
        vertical-align: middle;
      }

      .page-button2 span {
        cursor: pointer;
        display: inline-block;
        position: relative;
        transition: 0.5s;
      }

      .page-button2 span::after {
        content: ">>";
        position: absolute;
        opacity: 0;
        top: 0;
        right: -20px;
        transition: 0.5s;
      }

      .page-button2:hover span {
        padding-right: 30px;
      }

      .page-button2:hover span::after {
        opacity: 1;
        right: 0;
      }

}

.pagination-container {
  @media screen and (max-width: 768px) {
    display: flex;
    flex-direction: row; // 改为水平排列
    justify-content: center;
    align-items: center;
    gap: 10px;
    padding: 0 15px;
    margin: 15px 0;

    .page-button1,
    .page-button2 {
      width: auto; // 自适应宽度
      min-width: 100px;
      font-size: 14px;
      padding: 8px 15px;
      margin: 0; // 移除默认边距
    }

    > span {
      font-size: 13px;
      white-space: nowrap; // 防止文字换行
    }
  }
}

.el-button[type="text"] {
  color: #909399;

  &:hover {
    color: #409EFF;
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
  color: #909399;

  i {
    margin-right: 4px;
  }

  &:hover {
    color: #409EFF;
  }
}

.action-buttons {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 10px 0;
  border-top: 1px solid #f0f0f0;

  a.el-button,
  .el-button {
    flex: 1;
    display: inline-flex;
    align-items: center;
    justify-content: center;
    padding: 0;
    height: 32px;
    font-size: 13px;
    color: #909399;
    text-decoration: none;
    transition: all 0.3s;

    i {
      margin-right: 4px;
      font-size: 14px;
    }

    &:hover {
      color: #409EFF;
      transform: translateY(-1px);
    }
  }
}

// 添加搜索建议相关样式
.search-box {

  .suggestion-item {
    padding: 4px 8px;

    &:hover {
      background-color: #f5f7fa;
      cursor: pointer;
    }
  }

  ::v-deep .el-autocomplete {
    width: 100%;

    .el-input__inner {
      border: none;
      border-radius: 24px;
      padding-right: 50px;
    }

    .el-input__suffix {
      right: 0;
    }
  }
}

// 自定义下拉菜单样式
::v-deep .el-autocomplete-suggestion {
  li {
    line-height: 1.5;
    padding: 8px 10px;

    &:hover {
      background-color: #f5f7fa;
    }
  }
}

::v-deep .my-autocomplete {
  width: 600px !important; /* 同步修改下拉菜单的宽度 */
  margin-top: 5px;
  border-radius: 12px;
  box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
  border: none;
  left: 0 !important; // 强制左对齐

  li {
    line-height: 1.5;
    padding: 8px 20px;
    font-size: 14px;

    &:hover {
      background-color: #f5f7fa;
    }

    .suggestion-item {
      color: #606266;
    }
  }

  .popper__arrow {
    display: none;
  }

  // 确保下拉菜单容器宽度一致
  .el-scrollbar {
    width: 100%;

    .el-scrollbar__wrap {
      width: 100%;

      .el-scrollbar__view {
        width: 100%;
      }
    }
  }
}

// 搜索区域移动端适配
.search-container {
  @media screen and (max-width: 768px) {
    width: 95%;
    flex-direction: column;
    gap: 10px;
    margin: 20px auto;

    .search-box {
      width: 100%;
    }

    .filter-toggle {
      align-self: flex-start;
    }
  }
}

// 筛选卡片移动端适配
.filter-card {
  @media screen and (max-width: 768px) {
    width: 95%;

    .filter-item {
      margin-bottom: 20px;

      .platform-checkboxes {
        display: grid;
        grid-template-columns: repeat(auto-fit, minmax(120px, 1fr));
        gap: 10px;
      }

      .price-range {
        flex-wrap: wrap;

        .price-input {
          flex: 1;
          min-width: 120px;
        }
      }

      .sort-buttons {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 10px;
      }
    }
  }
}

// 商品列表移动端适配
.products {
  @media screen and (max-width: 768px) {
    padding: 0 10px;

    .el-row {
      margin: 0 !important;
    }

    .el-col {
      width: 100%;
      padding: 0 !important;
    }

    .product-card {
      width: 100%;
      max-width: none;
      margin: 0 auto 15px;
      height: auto; // 让卡片高度自适应

      .product-image-wrapper {
        height: 0;
        padding-bottom: 100%;
        position: relative;

        img {
          position: absolute;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
          object-fit: cover;
        }
      }

      .product-content {
        padding: 15px;
        height: auto; // 让内容区域高度自适应
        display: flex;
        flex-direction: column;

        .title-section {
          font-size: 14px;
          -webkit-line-clamp: 2;
          line-height: 1.4;
        }

        .info-section {
          flex-wrap: wrap;
          gap: 8px;
        }

        .action-section {
          margin-top: 10px;
          border-top: 1px solid #f0f0f0;

          .action-buttons {
            display: flex;
            justify-content: space-between;
            padding: 10px 0 0 0;
            gap: 8px;

            a.el-button,
            .el-button {
              flex: 1;
              min-width: 0; // 允许按钮缩小
              font-size: 12px;
              padding: 8px 0;
              margin: 0;
              height: auto;
              display: flex;
              flex-direction: column;
              align-items: center;
              justify-content: center;
              line-height: 1.2;
              white-space: normal;
              text-align: center;

              i {
                font-size: 16px;
                margin: 0 0 4px 0;
              }

              span {
                display: block;
                font-size: 12px;
              }
            }
          }
        }
      }
    }
  }
}

// 分页控件移动端适配
.pagination-container {
  @media screen and (max-width: 768px) {
    padding: 0 10px;
    margin: 15px 0;

    .page-button1,
    .page-button2 {
      width: 100px;
      font-size: 14px;
      padding: 8px;
    }

    > span {
      font-size: 13px;
      display: block;
      margin: 10px 0;
    }
  }
}

// 对话框移动端适配
::v-deep .el-dialog {
  @media screen and (max-width: 768px) {
    width: 90% !important;
    margin: 5vh auto !important;

    .el-dialog__title {
      font-size: 16px;
    }

    .el-dialog__body {
      padding: 15px;
    }
  }
}

// 搜索建议下拉菜单移动端适配
::v-deep .my-autocomplete {
  @media screen and (max-width: 768px) {
    width: calc(100vw - 40px) !important; // 减去左右边距
    left: 50% !important;
    transform: translateX(-50%);
    margin-top: 5px;
  }
}
</style>
