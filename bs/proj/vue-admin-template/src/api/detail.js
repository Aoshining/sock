import request from '@/utils/request'

export function getDetail(id) {
  return request({
    url: '/detail',
    method: 'get',
    params: {
      id: id
    }
  })
}

export function addReview(review) {
  return request({
    url: '/detail',
    method: 'post',
    data: {
      product_id: review.product_id,
      user_id: review.user_id,
      user_name: review.user_name,
      grade: review.grade,
      comment: review.comment
    }
  })
}
