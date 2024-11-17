<template>
  <div class="dashboard-container">
    <div class="search-box">
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
</template>

<script>
import { mapGetters } from 'vuex'

export default {
  data() {
    return {
      searchQuery: '',
    }
  },
  computed: {
    ...mapGetters([
      'name'
    ])
  }
}
</script>

<style lang="scss" scoped>
.dashboard-container {


  .search-box {
    margin: 50px auto auto;
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
}
</style>
