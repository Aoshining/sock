<script>
	import {
		getDetail,
		addReview
	} from '@/api/like'

	export default {
		filters: {
			statusFilter(status) {
				const statusMap = {
				published: 'success',
				draft: 'gray',
				deleted: 'danger'
				}
				return statusMap[status]
			}
		},
		data() {
			return {
        id: 0,
				newReview: {
          product_id: 0,
          user_id: 0,
          user_name: '',
          grade: 0.0,
          comment: ''
        },
        price_record: [],
        review: []
			}
		},
		created() {
			this.getDetail()
		},
		methods: {
			getDetail() {
				getDetail(this.id).then(response => {
					if (response['error'] === 'success') {
            // this.price_record = []
            // this.review = []
            // let records = response['product_price']
            // records.forEach(singleRecord => {
            //   this.price_record.push(singleRecord)
            // })
            // let reviews = response['review']
            // reviews.forEach(singleReview => {
            //   this.review.push(singleReview)
            // })
            this.price_record = response['product_price']
            this.review = response['review']
					} else {
						this.$message.error('加载失败')
						console.log(response['error'])
					}
				})
		},
		addReview() {
        this.newReview = {}
			  addReview(this.newReview).then(response => {
          if (response.error_num === 0) {
            this.getList()
            this.input_bookname = ''
          } else {
            this.$message.error('新增书籍失败，请重试')
            console.log(response['msg'])
          }
			})
		}
	}
}
</script>

<template>
	<div class="app-container">
<!--	  <el-row display="margin-top:10px">-->
<!--	    <el-input v-model="input_bookname" placeholder="请输入书名" style="display:inline-table; width: 30%; float:left"></el-input>-->
<!--	    <el-button type="primary" @click="addBook()" style="float:left; margin: 2px;">新增</el-button>-->
<!--	  </el-row>-->
<!--	  <el-row>-->
<!--	    <el-table :data="list_book" element-loading-text="Loading" border fit highlight-current-row>-->
<!--	      <el-table-column align="center" label="ID" width="95">-->
<!--	        <template slot-scope="scope">-->
<!--	          {{ scope.row.pk }}-->
<!--	        </template>-->
<!--	      </el-table-column>-->
<!--	      <el-table-column label="Book_name">-->
<!--	        <template slot-scope="scope">-->
<!--	          {{ scope.row.fields.book_name }}-->
<!--	        </template>-->
<!--	      </el-table-column>-->
<!--	      <el-table-column label="Time" align="center">-->
<!--	        <template slot-scope="scope">-->
<!--	          <span>{{ scope.row.fields.add_time }}</span>-->
<!--	        </template>-->
<!--	      </el-table-column>-->
<!--	    </el-table>-->
<!--	  </el-row>-->
	</div>
</template>

<style scoped lang="scss">

</style>
