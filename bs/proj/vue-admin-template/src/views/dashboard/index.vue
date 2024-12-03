<template>
  <div class="dashboard-container">
    <div class="search-box">
      <form>
          <input
            type="text"
            placeholder="探索你心仪的商品吧..."
            v-model="productName"
          />
        <button class="search-btn" type="submit" @click="checkLogin()">
          <img src="./search.png" alt="搜索">
        </button>
      </form>
    </div>

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

    <div class="product-filter">
      <el-row type="flex" align="middle" style="margin-bottom: 10px">
        <el-col :span="5" :xs="24">
          <el-checkbox-group v-model="selectedPlatforms">
            <el-checkbox label="京东">京东</el-checkbox>
            <el-checkbox label="唯品会">唯品会</el-checkbox>
            <el-checkbox label="苏宁">苏宁易购</el-checkbox>
          </el-checkbox-group>
        </el-col>
      </el-row>

        <el-row type="flex" align="middle">
        <el-col :span="2" :xs="24">
          <el-input v-model="priceRange[0]" placeholder="最低价" @input="handlePriceChange"></el-input>
        </el-col>
        <el-col :span="1" :xs="24" style="text-align: center;">
          ——
        </el-col>
        <el-col :span="2" :xs="24">
          <el-input v-model="priceRange[1]" placeholder="最高价" @input="handlePriceChange"></el-input>
        </el-col>

        <el-col :span="2" :xs="24" style="margin-left: 36px; margin-right: 20px">
          <el-button type="primary" @click="sortProducts('low')">价格从低到高</el-button>
        </el-col>
        <el-col :span="2" :xs="24">
          <el-button type="primary" @click="sortProducts('high')">价格从高到低</el-button>
        </el-col>
      </el-row>
    </div>

    <div class="products">
    <el-row>
      <el-col :span="6" :xs="24" v-for="product in filteredProducts" :key="product.title" style="display: flex; justify-content: center;">
        <el-card class="product-card">
          <img :src="product.img" class="product-image" alt="商品图片">
          <div style="padding: 14px;">
            <div class="price" style="color: brown; font-weight: bold; font-size: 26px;">
              ￥{{ product.price }}
            </div>
            <div class="title" style="font-weight: bold; margin-top: 10px; font-size: 14px;">
              {{ product.title }}
            </div>
            <div class="sales" style="color: #666666; margin-top: 10px; font-size: 14px;">
              已售 <span style="color: #1482f0">{{ product.sales }}</span>
            </div>
            <div class="shop" style="color: #666666; margin-top: 10px; font-size: 14px;">
              <svg-icon :icon-class='product.platform'/> {{ product.shop }}
            </div>
            <a :href="product.link" target="_blank" class="product-detail-link">查看详情</a>
          </div>
        </el-card>
      </el-col>
    </el-row>
    </div>

    <div class="pagination-container" style="text-align: center; margin-top: 20px">
      <button
        class="page-button1"
        :disabled="currentPage === 1"
        @click="changePage(currentPage - 1)">
        <span>上一页</span>
      </button>
      <span>第 {{ currentPage }} 页，共 {{ pageCount }} 页</span>
      <button
        class="page-button2"
        :disabled="currentPage === pageCount"
        @click="changePage(currentPage + 1)">
        <span>下一页</span>
      </button>
    </div>
  </div>
</template>

<script>

import axios from "axios";

export default {
  data() {
    return {
      currentPage: 1, // 当前页码
      pageSize: 8, // 每页显示的产品数量
      allPlatforms: ['京东', '唯品会', '苏宁'],
      selectedPlatforms: [],
      productName: '',
      products: [
        {
          img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
          title: '毒蝰v3pro',
          price: '1699',
          sales: '10000+',
          shop: '雷蛇京东自营店',
          platform: '京东',
          link: 'https://item.jd.com/10101957501630.html',
        },{
          img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
          title: '毒蝰v3pro',
          price: '1499',
          sales: '10000+',
          shop: '雷蛇京东自营店',
          platform: '京东',
          link: 'https://item.jd.com/10101957501630.html',
        },{
          img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
          title: '毒蝰v3pro',
          price: '1299',
          sales: '10000+',
          shop: '雷蛇京东自营店',
          platform: '京东',
          link: 'https://item.jd.com/10101957501630.html',
        },{
          img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
          title: '毒蝰v3pro',
          price: '1399',
          sales: '10000+',
          shop: '雷蛇京东自营店',
          platform: '京东',
          link: 'https://item.jd.com/10101957501630.html',
        },{
          img: 'https://img10.360buyimg.com/n7/jfs/t1/241078/7/24217/84262/673beddfF8355aea3/2ae48dacbe2448b8.jpg',
          title: '毒蝰v3pro',
          price: '1599',
          sales: '10000+',
          shop: '雷蛇京东自营店',
          platform: '京东',
          link: 'https://item.jd.com/10101957501630.html',
        },
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
      sortType: 'default' // 排序方式
    }
  },
  computed: {
    filteredProducts() {
      // 将 priceRange 中的空字符串转换为 null 以表示无限制
      // 如果没有选择任何平台，则默认选择所有平台
      const selectedPlatforms = this.selectedPlatforms.length === 0 ? this.allPlatforms : this.selectedPlatforms
      // 将 priceRange 中的空字符串转换为 null 以表示无限制
      const [minPrice, maxPrice] = this.priceRange.map(range => range === '' ? null : parseFloat(range))
      // 根据平台、价格范围和排序类型过滤和排序产品
      let filteredAndSortedProducts = this.products.filter(product =>
        selectedPlatforms.includes(product.platform) &&
        (minPrice === null || product.price >= minPrice) &&
        (maxPrice === null || product.price <= maxPrice)
      )
      if (this.sortType === 'low') {
        filteredAndSortedProducts = filteredAndSortedProducts.sort((a, b) => a.price - b.price)
      } else if (this.sortType === 'high') {
        filteredAndSortedProducts = filteredAndSortedProducts.sort((a, b) => b.price - a.price)
      }
      const start = (this.currentPage - 1) * this.pageSize;
      const end = this.currentPage * this.pageSize;
      return filteredAndSortedProducts.slice(start, end)
    },

    pageCount() {
      // 计算总页数
      return Math.ceil(this.products.length / this.pageSize);
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
          this.loading = this.$loading({fullscreen: false, text: '稍等一下下，马上就加载出来啦...', target: '.products'})
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
          this.loading = this.$loading({fullscreen: false, text: '稍等一下下，马上就加载出来啦...', target: '.products'})
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
        this.loading = this.$loading({fullscreen: false, text: '稍等一下下，马上就加载出来啦...', target: '.products'})
        this.Search()
      }
    },

  },

  mounted() {

  },

  methods: {
    changePage(page) {
      this.currentPage = page;
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
      this.loading = this.$loading({fullscreen: false, text: '稍等一下下，马上就加载出来啦...', target: '.products'})
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
      this.$message.success('查询中，请稍等')
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
    }
  }
}
</script>

<style lang="scss" scoped>
.dashboard-container {


  .search-box {
    margin: 50px auto 40px;
    position: relative;
    width: 400px; /* 增加搜索框的宽度 */
    height: 50px; /* 增加搜索框的高度 */
    background-color: #ffffff;
    border-radius: 25px; /* 圆润的搜索框 */
    overflow: hidden;
    display: flex;
    align-items: center;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* 添加阴影以增加立体感 */

    input {
      width: 100%;
      height: 100%;
      padding: 0 20px;
      border: none;
      background: none;
      outline: none;
      color: #333;
      font-size: 16px;
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

  .product-card {
    margin-bottom: 10px;
    height: 500px;
    width: 300px;
  }

  .product-image {
    width: 100%; /* 使图片宽度适应容器 */
    height: 200px; /* 设置图片高度 */
    object-fit: cover; /* 裁剪图片以适应容器 */
  }

  .product-detail-link {
    display: inline-block;
    margin-top: 10px;
    font-size: 14px;
    color: #9ea0a1; /* Element UI 主题色 */
    text-decoration: none; /* 去除下划线 */
  }

  .product-detail-link:hover {
    text-decoration: underline; /* 鼠标悬浮时添加下划线 */
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

  .product-filter {
    margin-left: 36px;
    margin-bottom: 30px;
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
</style>
